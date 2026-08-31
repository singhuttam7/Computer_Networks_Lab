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

    // To ensure a frame is lost only once
    bool frame4_lost = false;
    bool frame8_lost = false;

    std::cout << "================== GO-BACK-N ARQ ==================\n";
    std::cout << "Window Size = " << window_size << "\n\n";

    while (base < total_frames) {

        int window_end = std::min(base + window_size, total_frames);

        std::cout << "[SENDER] Sending window starting from Frame "
                  << base + 1 << ":\n\n";

        int lost_frame = -1;

        // ------------------------------------------------
        // STEP 1: Sender sends all frames in the window
        // ------------------------------------------------

        for (int i = base; i < window_end; i++) {

            total_transmissions++;

            std::cout << "[SENDER] Sends Frame "
                      << i + 1
                      << " (Data: " << frames[i] << ")";

            // Frame 4 is lost only on its first transmission
            if (i == 3 && !frame4_lost) {

                frame4_lost = true;
                lost_frame = i;

                std::cout << " --> LOST!";
            }

            // Frame 8 is lost only on its first transmission
            else if (i == 7 && !frame8_lost) {

                frame8_lost = true;
                lost_frame = i;

                std::cout << " --> LOST!";
            }

            else {

                std::cout << " --> Sent";
            }

            std::cout << "\n";
        }

        std::cout << "\n";

        // ------------------------------------------------
        // STEP 2: Receiver processes the window
        // ------------------------------------------------

        if (lost_frame != -1) {

            // Frames before the lost frame are received
            for (int i = base; i < lost_frame; i++) {

                std::cout << "[RECEIVER] Received Frame "
                          << i + 1
                          << " (Data: " << frames[i] << ")\n";

                std::cout << "[RECEIVER] Sent ACK "
                          << i + 1 << "\n";
            }

            // Lost frame
            std::cout << "[RECEIVER] Frame "
                      << lost_frame + 1
                      << " was LOST. No ACK received.\n";

            // Frames after lost frame are discarded
            for (int i = lost_frame + 1; i < window_end; i++) {

                std::cout << "[RECEIVER] Discarded Frame "
                          << i + 1
                          << " (Out of order)\n";
            }

            // ------------------------------------------------
            // STEP 3: Timeout and Go-Back-N retransmission
            // ------------------------------------------------

            std::cout << "\n[SENDER] Timeout for Frame "
                      << lost_frame + 1 << "!\n";

            std::cout << "[GO-BACK-N] Retransmitting from Frame "
                      << lost_frame + 1 << "\n\n";

            // Go back to the lost frame
            base = lost_frame;
        }

        else {

            // ------------------------------------------------
            // STEP 4: All frames in the window are received
            // ------------------------------------------------

            for (int i = base; i < window_end; i++) {

                std::cout << "[RECEIVER] Received Frame "
                          << i + 1
                          << " (Data: " << frames[i] << ")\n";

                std::cout << "[RECEIVER] Sent ACK "
                          << i + 1 << "\n";
            }

            std::cout << "\n[SENDER] Cumulative ACK "
                      << window_end
                      << " received!\n";

            std::cout << "[WINDOW] Sliding window forward.\n\n";

            base = window_end;
        }
    }

    std::cout << "====================================================\n";
    std::cout << "All frames successfully transmitted!\n";
    std::cout << "Total transmission attempts: "
              << total_transmissions << "\n";
    std::cout << "====================================================\n";

    return 0;
}

/***
Frame 1 → Received → ACK 1
Frame 2 → Received → ACK 2
Frame 3 → Received → ACK 3
Frame 4 → LOST
Frame 5 → Discarded
Frame 6 → Discarded
Frame 7 → Discarded

Timeout for Frame 4

Frame 4 → Retransmitted → Received → ACK 4
Frame 5 → Received → ACK 5
Frame 6 → Received → ACK 6
Frame 7 → Received → ACK 7
Frame 8 → LOST

Timeout for Frame 8

Frame 8 → Retransmitted → Received → ACK 8
Frame 9 → Received → ACK 9
***/
