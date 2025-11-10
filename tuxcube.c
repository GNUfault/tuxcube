#include "raylib.h"
#include "rlgl.h"
#include "tux.h"

int main(void) {
    SetTraceLogLevel(LOG_WARNING);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Tux");
    
    Camera3D camera = {
        .position = (Vector3){ 10.0f, 10.0f, 10.0f },
        .target = (Vector3){ 0.0f, 0.0f, 0.0f },
        .up = (Vector3){ 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };
    
    Image image = LoadImageFromMemory(
        ".png",
        tux,
        tux_len
    );

    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    
    Model cube = LoadModelFromMesh(GenMeshCube(5.0f, 5.0f, 5.0f));
    cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    
    float rotation = 0.0f;

    SetTargetFPS(60);
    HideCursor();
    
    while (!WindowShouldClose()) {
        rotation += 1.0f * GetFrameTime() * 60.0f;
        
        BeginDrawing();    
            ClearBackground(BLACK);
            BeginMode3D(camera);
                rlPushMatrix();
                    rlRotatef(rotation, 0.0f, 1.0f, 0.0f);
		    DrawModel(cube, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
                rlPopMatrix();
            EndMode3D();
        EndDrawing();
    }
    
    UnloadTexture(texture);
    UnloadModel(cube);
    CloseWindow();
    
    return 0;
}
