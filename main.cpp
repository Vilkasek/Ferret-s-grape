#define __GLIBC_USE(X) 0

#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspkernel.h>

#include <raylib.h>

PSP_MODULE_INFO("Ferret\'s Grape", 0, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

void update() {}
void render() {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  DrawText("Hello, World!", 140, 120, 20, BLACK);

  EndDrawing();
}

int main() {
  InitWindow(480, 272, "Ferret\'s Grape");

  while (!WindowShouldClose()) {
    update();
    render();
  }

  CloseWindow();
  return 0;
}
