#pragma once

#include <GLFW/glfw3.h>

#include "Core/Utils.hpp"
#include "Events/IEvent.hpp"

namespace EventSystem {

    class Window_Impl {
    public:
        using EventFunc = std::function<void(Event& event)>;

        [[nodiscard]] inline const std::string& GetTitle() const { return m_Title; }
        [[nodiscard]] inline int GetWidth() const { return m_Width; }
        [[nodiscard]] inline int GetHeight() const { return m_Height; }
        [[nodiscard]] inline bool IsOpen() const { return !glfwWindowShouldClose(m_Handle); }

        void PollEvents() const;
        void SwapBuffers() const;

        friend class Singleton<Window_Impl>;

    private:
        using HandleType = GLFWwindow;

        static void MouseMovedCallback(HandleType* handle, double x, double y);
        static void MouseScrolledCallback(HandleType* handle, double offsetX, double offsetY);
        static void MouseButtonCallback(HandleType* handle, int button, int action, int mods);
        static void KeyCallback(HandleType* handle, int key, int scancode, int action, int mods);
        static void TypedCallback(HandleType* handle, unsigned int key);
        static void WindowResizeCallback(HandleType* handle, int width, int height);
        static void WindowCloseCallback(HandleType* handle);
        static void WindowMaximizedCallback(HandleType* handle, int maximized);
        static void WindowMinimizedCallback(HandleType* handle, int minimized);
        static void WindowFocusCallback(HandleType* handle, int focused);

    private:
        Window_Impl(std::string title, int width, int height);
        ~Window_Impl();

    private:
        std::string m_Title;
        int         m_Width;
        int         m_Height;
        HandleType* m_Handle;
        EventFunc   m_EventFunc;

    }; // class Window

    using Window = Singleton<Window_Impl>;

} // namespace EventSystem