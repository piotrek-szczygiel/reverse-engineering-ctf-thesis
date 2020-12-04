#include <raylib.h>

unsigned char flag[] = {

    0x3f, 0xf4, 0x2f, 0xad, 0x53, 0x37, 0x99, 0xca, 0x8d, 0x30, 0xf7, 0x2b,
    0xaa, 0xd8, 0xca, 0xd9, 0x35, 0x2f, 0xf4, 0x70, 0x90, 0x4a, 0xd7, 0xf2,
    0x59, 0xbd, 0x1d, 0xac
};

void decrypt_flag()
{
    for (unsigned int m = 0; m < sizeof(flag); ++m) {
        unsigned char c = flag[m];
        c ^= 0xf1;
        c += m;
        c ^= 0x8e;
        c -= m;
        c ^= 0x19;
        c = -c;
        c -= m;
        c ^= 0x80;
        c = -c;
        c = ~c;
        c ^= 0x16;
        c += m;
        c = (c >> 0x7) | (c << 0x1);
        c ^= 0xfd;
        c += m;
        c = ~c;
        c -= m;
        c = ~c;
        c -= 0xe1;
        c = ~c;
        c += m;
        c = -c;
        c ^= 0xe5;
        c = ~c;
        c -= m;
        c = (c >> 0x2) | (c << 0x6);
        c ^= 0xc7;
        c -= 0x79;
        c = (c >> 0x5) | (c << 0x3);
        c += 0x61;
        c = (c >> 0x2) | (c << 0x6);
        c += m;
        c ^= m;
        c -= 0x35;
        c = ~c;
        c += 0x15;
        c ^= m;
        c -= m;
        c = ~c;
        c = (c >> 0x2) | (c << 0x6);
        c += m;
        c ^= m;
        c -= 0x8b;
        c = -c;
        c ^= m;
        c += 0x10;
        c ^= 0xfc;
        c -= m;
        c ^= 0x29;
        c = (c >> 0x6) | (c << 0x2);
        c = ~c;
        c = (c >> 0x7) | (c << 0x1);
        c ^= m;
        c += 0x19;
        c = -c;
        c -= 0x4d;
        c ^= m;
        c += 0xda;
        c = ~c;
        c ^= 0xff;
        c = (c >> 0x2) | (c << 0x6);
        c = -c;
        c = ~c;
        c = -c;
        c ^= 0x23;
        c -= m;
        c = -c;
        c ^= 0x8d;
        c = (c >> 0x6) | (c << 0x2);
        c ^= 0xde;
        c += m;
        c ^= 0xc2;
        c = -c;
        c = (c >> 0x3) | (c << 0x5);
        c = ~c;
        c -= m;
        c = (c >> 0x3) | (c << 0x5);
        c ^= 0xe9;
        c = -c;
        c ^= m;
        c -= m;
        c ^= 0xd0;
        c = ~c;
        c += 0x7d;
        c = -c;
        c += 0xe9;
        c ^= m;
        c -= 0x74;
        c ^= m;
        c += 0xd;
        c = (c >> 0x7) | (c << 0x1);
        c = ~c;
        c = (c >> 0x3) | (c << 0x5);
        c += 0xa2;
        c ^= 0x16;
        c -= 0xe0;
        c = -c;
        c = ~c;
        c ^= m;
        c += m;
        c ^= 0x3a;
        c = (c >> 0x7) | (c << 0x1);
        c -= m;
        c = (c >> 0x1) | (c << 0x7);
        c -= m;
        c ^= 0x94;
        c += 0x19;
        c = (c >> 0x7) | (c << 0x1);
        c ^= m;
        c += 0xbd;
        c ^= m;
        c += 0x26;
        c = -c;
        c = (c >> 0x1) | (c << 0x7);
        c += 0x8d;
        c ^= 0x87;
        c = ~c;
        c -= 0xdb;
        c = ~c;
        c ^= 0x29;
        c = ~c;
        c += 0x95;
        c = -c;
        c = ~c;
        c += m;
        c = ~c;
        c -= 0xf8;
        c = (c >> 0x3) | (c << 0x5);
        flag[m] = c;
    }
}

bool show_flag()
{
    return false;
}

int main()
{
    if (show_flag()) {
        decrypt_flag();
    }

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800, 200, "200-game");
    SetTargetFPS(60);

    Vector2 position = { 100, 100 };

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) {
            position.x += 5;
        } else if (IsKeyDown(KEY_LEFT)) {
            position.x -= 5;
        }

        if (position.x < 100) {
            position.x = 100;
        } else if (position.x > 700) {
            position.x = 700;
        }

        bool finished = false;
        if (position.x == 700) {
            finished = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(650, 50, 100, 100, GOLD);
        DrawCircleV(position, 25, MAROON);

        if (finished) {
            if (show_flag()) {
                DrawText((const char*)flag, 100, 90, 20, GREEN);
            } else {
                DrawText("You have not unlocked access to the flag!", 100, 90,
                    20, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}