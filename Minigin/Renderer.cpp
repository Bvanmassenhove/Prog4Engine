#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_opengl2.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/imgui_plot.h"
#include <chrono>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	//imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

//void Exercise1(float* data)
//{
//	std::vector<int> arr{};
//	arr.resize(1000000);
//
//	int step = 0;
//	for (size_t stepsize = 1; stepsize <= 1024; stepsize *= 2)
//	{
//		auto start = std::chrono::high_resolution_clock::now();
//		for (size_t amount = 0; amount < 3; amount++)
//		{
//
//			for (size_t i = 0; i < arr.size(); i += stepsize)
//			{
//				arr[i] *= 2;
//			}
//		}
//		auto end = std::chrono::high_resolution_clock::now();
//		auto elapsedTime = duration_cast<std::chrono::microseconds>(end - start).count();
//		data[step] = (float)elapsedTime;
//		++step;
//	}
//	
//}
//struct Transform
//{
//	float matrix[16] = {
//		1,0,0,0,
//		0,1,0,0,
//		0,0,1,0,
//		0,0,0,1 };
//};
//class GameObject3DAlt
//{
//public:
//	Transform* transformAlt;
//	int ID;
//};
//class GameObject3D
//{
//public:
//	Transform transform;
//	int ID;
//};
//void Exercise2(float* data)
//{
//	std::vector<GameObject3D> arrGameObj{};
//	arrGameObj.resize(1000000);
//	
//	int step = 0;
//	for (size_t stepsize = 1; stepsize <= 1024; stepsize *= 2)
//	{
//		auto start = std::chrono::high_resolution_clock::now();
//		for (size_t amount = 0; amount < 3; amount++)
//		{
//
//			for (size_t i = 0; i < arrGameObj.size(); i += stepsize)
//			{
//				arrGameObj[i].ID *= 2;
//			}
//		}
//		auto end = std::chrono::high_resolution_clock::now();
//		auto elapsedTime = duration_cast<std::chrono::microseconds>(end - start).count();
//		data[step] = (float)elapsedTime;
//		++step;
//	}
//
//}
//void Exercise3(float* data)
//{
//	std::vector<GameObject3D> arrGameObjAlt{};
//	arrGameObjAlt.resize(1000000);
//
//	int step = 0;
//	for (size_t stepsize = 1; stepsize <= 1024; stepsize *= 2)
//	{
//		auto start = std::chrono::high_resolution_clock::now();
//		for (size_t amount = 0; amount < 3; amount++)
//		{
//
//			for (size_t i = 0; i < arrGameObjAlt.size(); i += stepsize)
//			{
//				arrGameObjAlt[i].ID *= 2;
//			}
//		}
//		auto end = std::chrono::high_resolution_clock::now();
//		auto elapsedTime = duration_cast<std::chrono::microseconds>(end - start).count();
//		data[step] = (float)elapsedTime;
//		++step;
//	}
//
//}
//constexpr size_t data_count = 10;
//float y_data1[data_count];
//float y_data2[data_count];
//float y_data3[data_count];
void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	//imgui
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	/*ImGui::Begin("Exercise 1");
	
	if (ImGui::Button("trash the cash"))
	{
		Exercise1(y_data1);
	}
	
	ImGui::PlotConfig conf1;
	conf1.values.ys = y_data1;
	conf1.values.count = data_count;
	conf1.scale.min = 0;
	conf1.scale.max = 50000;
	conf1.tooltip.show = true;
	conf1.tooltip.format = "x=%.2f, y=%.52f";
	conf1.grid_x.show = true;
	conf1.grid_y.show = true;
	conf1.frame_size = ImVec2(200, 100);
	conf1.line_thickness = 2.f;
	ImGui::Plot("plot1", conf1);
	ImGui::End();

	ImGui::Begin("Exercise 2");

	if (ImGui::Button("trash the cash game objects"))
	{
		Exercise2(y_data2);
	}

	ImGui::PlotConfig conf2;
	conf2.values.ys = y_data2;
	conf2.values.count = data_count;
	conf2.scale.min = 0;
	conf2.scale.max = 50000;
	conf2.tooltip.show = true;
	conf2.tooltip.format = "x=%.2f, y=%.52f";
	conf2.grid_x.show = true;
	conf2.grid_y.show = true;
	conf2.frame_size = ImVec2(200, 100);
	conf2.line_thickness = 2.f;
	ImGui::Plot("plot2", conf2);

	if (ImGui::Button("trash the cash alt game objects"))
	{
		Exercise3(y_data3);
	}

	ImGui::PlotConfig conf3;
	conf3.values.ys = y_data3;
	conf3.values.count = data_count;
	conf3.scale.min = 0;
	conf3.scale.max = 50000;
	conf3.tooltip.show = true;
	conf3.tooltip.format = "x=%.2f, y=%.52f";
	conf3.grid_x.show = true;
	conf3.grid_y.show = true;
	conf3.frame_size = ImVec2(200, 100);
	conf3.line_thickness = 2.f;

	ImGui::Plot("plot3", conf3);


	ImGui::End();*/

	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	//imgui
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
