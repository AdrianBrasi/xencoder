#include "leif/leif.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cglm/types-struct.h>

#define WIN_MARGIN 20.0f
#define RGB 255.0f

static int win_height = 720, win_width = 1280;

void inputButton(LfFont font);

int main() {
    glfwInit();

    GLFWwindow *window =
        glfwCreateWindow(win_width, win_height, "XENCODER", NULL, NULL);
    glfwMakeContextCurrent(window);
    lf_init_glfw(win_width, win_height, window);

    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    LfFont titlefont = lf_load_font("./fonts/astron.otf", 100);
    LfFont mainfont = lf_load_font("./fonts/main.ttf", 40);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(31.0f / RGB, 35.0f / RGB, 53.0f / RGB, 1.0f);

        lf_begin();

        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}),
                     ((vec2s){win_width - WIN_MARGIN * 2.0f,
                     win_height - WIN_MARGIN * 2.0f}),
                     true);

        lf_push_font(&titlefont);
        lf_text("X-FILE ENCODER");
        lf_pop_font();

        inputButton(mainfont);

        lf_div_end();
        lf_end();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    lf_free_font(&mainfont);
    lf_free_font(&titlefont);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void inputButton(LfFont font){

    lf_push_font(&font);
    lf_set_ptr_x_absolute(WIN_MARGIN);
    lf_set_ptr_y_absolute(win_height/4.0f);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;
    props.margin_right = 0.0f;
    lf_push_style_props(props);
    lf_button_fixed("Select Input", 200, -1);
    lf_pop_style_props();
    lf_pop_font();
}
