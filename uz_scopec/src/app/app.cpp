// Application shell: GLFW window, ImGui docking + multi-viewport, ImPlot,
// initial dock layout, main loop.
//
// Multi-viewport is what makes "multiple plot windows" first-class: any plot
// window (or panel) dragged outside the main window becomes a real OS window.
#include "app/app.hpp"

#include <GLFW/glfw3.h>  // includes the system OpenGL header
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <implot.h>

#include <cstdio>
#include <filesystem>

#include "app/panels/panels.hpp"

namespace uz {
namespace {

constexpr const char* LAYOUT_INI = "uz_scopec_layout.ini";

void glfw_error(int code, const char* description) {
    std::fprintf(stderr, "GLFW error %d: %s\n", code, description);
}

void apply_style() {
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 4.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;
    style.TabRounding = 3.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;  // required with viewports
}

// First run (no layout ini): center = Scope 1 + tabs, right = Channels,
// bottom = Console — the uz_scope layout.
void build_default_layout(ImGuiID dockspace_id) {
    ImGui::DockBuilderRemoveNode(dockspace_id);
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->WorkSize);

    ImGuiID main_id = dockspace_id;
    ImGuiID right_id =
        ImGui::DockBuilderSplitNode(main_id, ImGuiDir_Right, 0.24f, nullptr, &main_id);
    ImGuiID bottom_id =
        ImGui::DockBuilderSplitNode(main_id, ImGuiDir_Down, 0.22f, nullptr, &main_id);

    ImGui::DockBuilderDockWindow("###plot0", main_id);
    ImGui::DockBuilderDockWindow("Control", main_id);
    ImGui::DockBuilderDockWindow("Trigger", main_id);
    ImGui::DockBuilderDockWindow("SlowData", main_id);
    ImGui::DockBuilderDockWindow("Logging", main_id);
    ImGui::DockBuilderDockWindow("Diagnostics", main_id);
    ImGui::DockBuilderDockWindow("Channels", right_id);
    ImGui::DockBuilderDockWindow("Console", bottom_id);
    ImGui::DockBuilderFinish(dockspace_id);
}

}  // namespace

int run_app(ScopeAppState& state, bool connect_on_start) {
    glfwSetErrorCallback(glfw_error);
    if (!glfwInit()) {
        std::fprintf(stderr, "glfwInit failed (no display?)\n");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window =
        glfwCreateWindow(1600, 950, "UltraZohm Scope (uz_scopec)", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // tear-off OS windows
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = LAYOUT_INI;
    bool first_run = !std::filesystem::exists(LAYOUT_INI);
    float xscale = 1.0f, yscale = 1.0f;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    if (xscale > 1.0f) io.FontGlobalScale = xscale;
    apply_style();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    PlotWindows plots;
    ChannelsPanel channels;
    ControlPanel control;
    TriggerPanel trigger;
    SlowDataPanel slowdata;
    LoggingPanel logging;
    DiagnosticsPanel diagnostics;
    ConsolePanel console;
    StatusBar statusbar;

    if (connect_on_start || state.config.auto_connect)
        state.commands.dispatch(state, "connect");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        state.poll_events();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Status bar first: reserves the bottom strip of the main viewport.
        float bar_height = ImGui::GetFrameHeight() * 1.25f;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        if (ImGui::BeginViewportSideBar("##statusbar", viewport, ImGuiDir_Down,
                                        bar_height,
                                        ImGuiWindowFlags_NoScrollbar |
                                            ImGuiWindowFlags_NoSavedSettings)) {
            statusbar.render(state);
        }
        ImGui::End();

        ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(
            0, viewport, ImGuiDockNodeFlags_PassthruCentralNode);
        if (first_run) {
            build_default_layout(dockspace_id);
            first_run = false;
        }

        plots.render(state);
        if (ImGui::Begin("Channels")) channels.render(state);
        ImGui::End();
        if (ImGui::Begin("Control")) control.render(state);
        ImGui::End();
        if (ImGui::Begin("Trigger")) trigger.render(state);
        ImGui::End();
        if (ImGui::Begin("SlowData")) slowdata.render(state);
        ImGui::End();
        if (ImGui::Begin("Logging")) logging.render(state);
        ImGui::End();
        if (ImGui::Begin("Diagnostics")) diagnostics.render(state);
        ImGui::End();
        if (ImGui::Begin("Console")) console.render(state);
        ImGui::End();

        ImGui::Render();
        int fb_w, fb_h;
        glfwGetFramebufferSize(window, &fb_w, &fb_h);
        glViewport(0, 0, fb_w, fb_h);
        glClearColor(0.06f, 0.06f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Multi-viewport: render the torn-off OS windows.
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }
        glfwSwapBuffers(window);
    }

    state.shutdown();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

}  // namespace uz
