#pragma once

fge::i32 main(fge::i32 argCount = 0, char* args[] = nullptr);

#if defined(_WIN32) && defined(NDEBUG)
fge::i32 WINAPI WinMain(HINSTANCE h_instance,
                        HINSTANCE h_prev_instance,
                        LPSTR lp_cmd_line,
                        fge::i32 n_cmd_show);
#endif