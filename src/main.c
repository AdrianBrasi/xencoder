#include "leif/leif.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cglm/types-struct.h>

#define WIN_MARGIN 20.0f
#define RGB 255.0f

static int win_height = 720, win_width = 1280;

void title(LfFont font1, LfFont font2);
void inputButton(LfFont font, const char *button_text, float ypos);

int main() {
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(win_width, win_height, "XENCODER", NULL, NULL);
    glfwMakeContextCurrent(window);
    lf_init_glfw(win_width, win_height, window);

    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    lf_set_theme(theme);

    LfFont titlefont = lf_load_font("./fonts/astron.otf", 120);
    LfFont subtitlefont = lf_load_font("./fonts/blue.ttf", 20);
    LfFont mainfont = lf_load_font("./fonts/blue.ttf", 20);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(13.0f / RGB, 2.0f / RGB, 33.0f / RGB, 1.0f);

        lf_begin();

        lf_div_begin(((vec2s){WIN_MARGIN, WIN_MARGIN}),
                     ((vec2s){win_width - WIN_MARGIN * 2.0f,
                     win_height - WIN_MARGIN * 2.0f}),
                     true);

        title(titlefont, subtitlefont);

        const char *select_video = "Select Video";
        inputButton(mainfont, select_video, 4.0f);

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

void title(LfFont font1, LfFont font2){
    lf_push_font(&font1);
    LfUIElementProps props = lf_get_theme().text_props;
    props.text_color = (LfColor){45, 226, 230, 255};
    lf_push_style_props(props);
    lf_text("X-ENCODER");
    lf_pop_font();

    lf_push_font(&font2);
    lf_set_ptr_x_absolute(WIN_MARGIN);
    lf_set_ptr_y_absolute(win_height/8.0f);
    lf_text("Prepare your media for the x-file by ensuring proper resolution & framerate");
    lf_pop_style_props();
    lf_pop_font();
}

void inputButton(LfFont font, const char *button_text, float ypos){

    lf_push_font(&font);
    lf_set_ptr_x_absolute(WIN_MARGIN);
    lf_set_ptr_y_absolute(win_height/ypos);
    LfUIElementProps props = lf_get_theme().button_props;
    props.margin_left = 0.0f;
    props.margin_right = 0.0f;
    props.color = (LfColor){84, 13, 110, 255};
    props.border_width = 4.0f;
    props.border_color = (LfColor){121, 30, 148, 255};
    props.corner_radius = 2.0f;
    props.text_color = (LfColor){255, 255, 255, 255};
    lf_push_style_props(props);
    lf_button_fixed(button_text, 200, -1);
    lf_pop_style_props();
    lf_pop_font();
}
