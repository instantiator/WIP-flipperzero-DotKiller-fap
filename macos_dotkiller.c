#include <furi.h>
#include <furi_hal.h>

#include <gui/gui.h>
#include <gui/elements.h>
#include <input/input.h>
#include <dialogs/dialogs.h>

#include <storage/storage.h>
#include <stream/stream.h>
#include <stream/buffered_file_stream.h>
#include <toolbox/stream/file_stream.h>

#include <stdlib.h>

#define TAG "DotKiller"

#define DOTFILE_VIEWER_APP_PATH_FOLDER "/ext"

typedef struct {
    int type;
    InputEvent input;
    bool confirmDelete;
} DotKillContext;

static void dotkill_input_callback(InputEvent* input_event, void* ctx) {
    FuriMessageQueue* queue = ctx;
    DotKillContext event = {
        .type = input_event->type,
        .input = *input_event,
        .confirmDelete = false,
    };
    furi_message_queue_put(queue, &event, FuriWaitForever);
}

static void dotkill_render_callback(Canvas* canvas, void* ctx) {
    DotKillContext* context = ctx;
    
    canvas_clear(canvas);
    
    canvas_draw_box(canvas, 0, 0, 127, 63);
	canvas_set_color(canvas, ColorWhite);

	canvas_draw_line(canvas, 0, 16, 127, 16);

	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 22, 30, "Delete all the useless");

	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 9, 40, ".dotfiles created by macOS");

	canvas_draw_icon(canvas, 65, 52, &I_Ok_btn_9x9);

	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 77, 60, "Kill them all");

	canvas_draw_icon(canvas, 4, 52, &I_Pin_back_arrow_10x8);

	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 18, 60, "Exit");

	canvas_set_font(canvas, FontPrimary);
	canvas_draw_str(canvas, 35, 12, "DOTKILLER");
	
	if (context->confirmDelete) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 32, 60, AlignCenter, AlignCenter, "Confirm delete all dotfiles?");
        elements_button_left(canvas, "No!");
        elements_button_right(canvas, "Yes!");
    }
}

static void delete_dotfiles_recursively(const char* path) {
    FileIterator* iterator = file_iterator_alloc(path, true);
    if (iterator != NULL) {
        while (file_iterator_next(iterator)) {
            if (file_iterator_current_type(iterator) == FileTypeRegular) {
                const char* filename = file_iterator_current_name(iterator);
                char filepath[128];
                snprintf(filepath, sizeof(filepath), "%s/%s", path, filename);

                // Check if the filepath matches any of the excluded dotfile paths
                bool isExcluded = strcmp(filepath, "/ext/apps_data/.passport.settings") == 0 ||
                                  strcmp(filepath, "/ext/apps_data/snake/.snake") == 0 ||
                                  strcmp(filepath, "/ext/badusb/.badusb.settings") == 0;

                if (!isExcluded && filename[0] == '.') {
                    file_remove(filepath);
                }
            } else if (file_iterator_current_type(iterator) == FileTypeDirectory) {
                const char* dirname = file_iterator_current_name(iterator);
                if (dirname[0] != '.') {
                    char dirpath[128];
                    snprintf(dirpath, sizeof(dirpath), "%s/%s", path, dirname);
                    delete_dotfiles_recursively(dirpath);
                }
            }
        }
        file_iterator_free(iterator);
    }
}


int32_t flipper_dotkiller_app(void* p) {
    UNUSED(p);
    FuriMessageQueue* queue = furi_message_queue_alloc(8, sizeof(DotKillContext));
    ViewPort* view_port = view_port_alloc();
    view_port_input_callback_set(view_port, dotkill_input_callback, queue);
    view_port_draw_callback_set(view_port, dotkill_render_callback, NULL);
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);
    bool processing = true;
    DotKillContext event;
    bool deleteConfirmed = false;
    do {
        if (furi_message_queue_get(queue, &event, FuriWaitForever) == FuriStatusOk) {
            if (event.input.type == InputTypeShort && event.input.key == InputKeyBack) {
                processing = false;
            } else if (event.input.type == InputTypeShort && event.input.key == InputKeyOk) {
                event.confirmDelete = true;
            } else if (event.input.type == InputTypeShort && event.input.key == InputKeyRight && event.confirmDelete) {
                deleteConfirmed = true;
                processing = false;
            } else if (event.input.type == InputTypeShort && event.input.key == InputKeyLeft && event.confirmDelete) {
                event.confirmDelete = false;
            }
        }
    } while (processing);
    view_port_enabled_set(view_port, false);
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);

    if (deleteConfirmed) {
        // Delete dotfiles
        delete_dotfiles_recursively(DOTFILE_VIEWER_APP_PATH_FOLDER);
    }

    return 0;
}