#include "mepch.h"
#include "RenderController.h"

RenderController& RenderController::get()
{
	static RenderController instance;
	return instance;
}

#ifdef USE_VULKAN

void RenderController::init(Window& renderWindow)
{
	vk::init(renderWindow.getGlfwWindowHandle());
}

void RenderController::terminate()
{
	vk::terminate();
}

MeshID RenderController::loadBGLSmesh(BGLSmeshBuffer& buffer)
{
	return MeshID();
}

void RenderController::render(MeshID mesh)
{
}

#else

void RenderController::init(Window& renderWindow)
{
	gl::init();
	viewport = { 0, 0, renderWindow.getSize().x, renderWindow.getSize().y };
	aspectRatio = (float)viewport.width / (float)viewport.height;
	fov = glm::radians(45.f);
	near = 0.1f;
	far = 100.f;
}

void RenderController::terminate()
{
	gl::terminate();
}

MeshID RenderController::addBGLSmesh(BGLSmeshBuffer& buffer)
{
	gl::VertexBuffer vbo = gl::createStaticVertexBuffer(buffer.vertexBufferSize, buffer.vertices);
	gl::ElementBuffer ebo = gl::createStaticElementBuffer(buffer.indexBufferSize, buffer.indices);

	gl::VertexAttribute posAttribute;
	posAttribute.vbo = vbo;
	posAttribute.dataType = GL_FLOAT;
	posAttribute.length = 3;
	posAttribute.stride = sizeof(Vertex);
	posAttribute.offset = (void*)0;

	gl::VertexAttribute normalAttribute;
	normalAttribute.vbo = vbo;
	normalAttribute.dataType = GL_FLOAT;
	normalAttribute.length = 3;
	normalAttribute.stride = sizeof(Vertex);
	normalAttribute.offset = (void*)offsetof(Vertex, normal);

	gl::VertexAttribute uvAttribute;
	uvAttribute.vbo = vbo;
	uvAttribute.dataType = GL_FLOAT;
	uvAttribute.length = 2;
	uvAttribute.stride = sizeof(Vertex);
	uvAttribute.offset = (void*)offsetof(Vertex, uv);

	gl::VertexArray vao = gl::createVertexArray(ebo, { posAttribute, normalAttribute, uvAttribute });

	return vao;
}

void RenderController::render(MeshID mesh, unsigned int count)
{
	static int a = 0;
	static gl::ShaderProgram shader;
	if (a == 0)
	{
		shader = gl::ShaderProgram("res/shaders/testVertex.glsl", "res/shaders/testFragment.glsl");
		a = 1;
	}
	shader.bind();
	shader.setUniformMatrix4("viewProjection", glm::perspective(glm::radians(45.f), 1980.f / 1080.f, 0.01f, 10000.f) * glm::lookAt(glm::vec3(1.3, 0.6, -0.1), glm::vec3(0, 0.6, 0), glm::vec3(0, 1, 0)));
	shader.setUniformMatrix4("model", glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.001)));
	gl::_drawElements(mesh, count);
}

#endif
