
#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::vector<int> frames = {
        12, 17, 70, 25, 98, 30, 87, 42, 56
    };

    int total_frames = frames.size();
    int window_size = 4;

    int total_transmissions = 0;
    int base = 0;

    // false = not acknowledged
    // true  = acknowledged
    std::vector<bool> acked(total_frames, false);

    std::cout
        << "================ SELECTIVE REPEAT ARQ ================\n";

    std::cout << "Window Size: " << window_size << "\n\n";

    while (base < total_frames) {

        int window_end =
            std::min(base + window_size, total_frames);

        std::cout
            << "[SENDER] Sending window starting from Frame "
            << base + 1 << "\n";

        // Store frames that are lost in this transmission round
        std::vector<bool> lost(total_frames, false);

        // =========================================================
        // STEP 1: SENDER SENDS ALL UNACKNOWLEDGED FRAMES
        // =========================================================

        for (int i = base; i < window_end; i++) {

            if (!acked[i]) {

                total_transmissions++;

                std::cout
                    << "[SENDER] Sends Frame "
                    << i + 1
                    << " (Data: "
                    << frames[i]
                    << ") -> ";

                // Every 4th transmission is lost
                if (total_transmissions % 4 == 0) {

                    lost[i] = true;

                    std::cout << "LOST IN TRANSIT\n";

                } else {

                    std::cout << "RECEIVED\n";
                }
            }
        }

        // =========================================================
        // STEP 2: RECEIVER PROCESSES FRAMES
        // =========================================================

        std::cout << "\n[RECEIVER STATUS]\n";

        for (int i = base; i < window_end; i++) {

            if (!acked[i]) {

                if (lost[i]) {

                    std::cout
                        << "  - Frame "
                        << i + 1
                        << ": Lost -> [NACK Sent]\n";

                } else {

                    acked[i] = true;

                    std::cout
                        << "  - Frame "
                        << i + 1
                        << ": Received OK -> [ACK Sent]\n";
                }
            }
        }

        // =========================================================
        // STEP 3: SLIDE WINDOW
        // =========================================================

        while (base < total_frames && acked[base]) {
            base++;
        }

        if (base < total_frames) {

            std::cout
                << "\n[SLIDING WINDOW] "
                << "Sender base advanced to Frame "
                << base + 1
                << "\n\n";

        } else {

            std::cout
                << "\n[SLIDING WINDOW] "
                << "All frames acknowledged.\n\n";
        }
    }

    // =============================================================
    // FINAL RESULT
    // =============================================================

    std::cout
        << "========================================================\n";

    std::cout
        << "SUCCESS: All "
        << total_frames
        << " frames delivered.\n";

    std::cout
        << "Total Transmissions Required: "
        << total_transmissions
        << " (Includes retransmissions)\n";

    std::cout
        << "========================================================\n";

    return 0;
}


