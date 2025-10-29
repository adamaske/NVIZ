#pragma once
#include "Core/Base.h"

enum class FramebufferTextureFormat
{
	None = 0,

	// Color
	RGBA8,
	RED_INTEGER,

	// Depth/stencil
	DEPTH24STENCIL8,

	// Defaults
	Depth = DEPTH24STENCIL8
};

struct FramebufferTextureSpecification
{
	FramebufferTextureSpecification() = default;
	FramebufferTextureSpecification(FramebufferTextureFormat format)
		: TextureFormat(format) {
	}

	FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	// TODO: filtering/wrap
};

struct FramebufferAttachmentSpecification
{
	FramebufferAttachmentSpecification() = default;
	FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
		: Attachments(attachments) {
	}

	std::vector<FramebufferTextureSpecification> Attachments;
};

struct FramebufferSpecification
{
	uint32_t Width = 0, Height = 0;
	FramebufferAttachmentSpecification Attachments;
	uint32_t Samples = 1;
	uint32_t ID = 0;// Unique identifier for the framebuffer
	bool SwapChainTarget = false;
};

class Framebuffer
{
public:
	Framebuffer(const FramebufferSpecification& sepc);
	~Framebuffer();

	void Invalidate();

	void Bind();
	void Unbind();

	void Resize(uint32_t width, uint32_t height);
	
	int ReadPixel(uint32_t attachmentIndex, int x, int y);
	
	void ClearAttachment(uint32_t attachmentIndex, int value);

	void DebugCheckColor(uint32_t expectedR, uint32_t expectedG, uint32_t expectedB);
	
	uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const { NVIZ_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }
	
	const FramebufferSpecification& GetSpecification() const { return m_Specification; }
	uint32_t GetID() const { return m_Specification.ID; }
private:

	uint32_t m_RendererID = 0;
	FramebufferSpecification m_Specification;

	std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
	FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

	std::vector<uint32_t> m_ColorAttachments;
	uint32_t m_DepthAttachment = 0;
};

