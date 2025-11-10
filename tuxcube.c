/*
 * tuxcube - Tux on a spinning cube with Raylib
 * Copyright (C) 2025  Connor Thomson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
