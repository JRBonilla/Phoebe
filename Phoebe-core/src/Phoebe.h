#pragma once

/// -------------------------
///  Main engine header file
/// -------------------------

#include "ph/Common.h"
#include "ph/Types.h"

#include "ph/app/Application.h"
#include "ph/app/InputManager.h"
#include "ph/app/Window.h"

#include "ph/audio/Sound.h"
#include "ph/audio/SoundManager.h"

#include "ph/debug/DebugMenu.h"
#include "ph/debug/DebugMenuItem.h"
#include "ph/debug/PerformanceInfo.h"

#include "ph/math/Math.h"

#include "ph/renderer/ForwardRenderer.h"
#include "ph/renderer/Layer2D.h"
#include "ph/renderer/Material.h"
#include "ph/renderer/Mesh.h"
#include "ph/renderer/MeshFactory.h"
#include "ph/renderer/Model.h"
#include "ph/renderer/Particle.h"
#include "ph/renderer/Renderer2D.h"
#include "ph/renderer/Renderer3D.h"
#include "ph/renderer/RenderSystem.h"
#include "ph/renderer/Scene.h"
#include "ph/renderer/Texture.h"
#include "ph/renderer/Texture2D.h"
#include "ph/renderer/TextureAtlas.h"
#include "ph/renderer/TextureCube.h"

#include "ph/renderer/lights/Light.h"
#include "ph/renderer/lights/LightSetup.h"

#include "ph/renderer/objects/BufferLayout.h"
#include "ph/renderer/objects/Framebuffer.h"
#include "ph/renderer/objects/IndexBuffer.h"
#include "ph/renderer/objects/VertexArray.h"
#include "ph/renderer/objects/VertexBuffer.h"

#include "ph/renderer/camera/Camera.h"
#include "ph/renderer/camera/EditorCamera.h"
#include "ph/renderer/camera/FPSCamera.h"
#include "ph/renderer/camera/OrthographicCamera.h"

#include "ph/renderer/fonts/Font.h"
#include "ph/renderer/fonts/FontManager.h"
#include "ph/renderer/fonts/FontAtlas.h"

#include "ph/renderer/renderables/Group.h"
#include "ph/renderer/renderables/Label.h"
#include "ph/renderer/renderables/Renderable2D.h"
#include "ph/renderer/renderables/Sprite.h"

#include "ph/renderer/shaders/Shader.h"
#include "ph/renderer/shaders/ShaderManager.h"
#include "ph/renderer/shaders/Uniform.h"
#include "ph/renderer/shaders/UniformBuffer.h"

#include "ph/sys/Allocator.h"
#include "ph/sys/Memory.h"

#include "ph/utils/FileManager.h"
#include "ph/utils/Image.h"
#include "ph/utils/Log.h"
#include "ph/utils/Timer.h"
#include "ph/utils/Timestep.h"
