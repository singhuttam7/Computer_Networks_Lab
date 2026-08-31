#include <iostream>
#include <vector>

int main() {
    int n = 10;
    // Hardcoded array as specified, or populated via input
    std::vector<int> frames = {20, 30, 45, 75, 65, 89, 93, 47, 25, 37};

    std::cout << "Displaying initial frames to send:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Frame " << i + 1 << ": " << frames[i] << "\n";
    }

    std::cout << "\n===================== Stop and Wait ARQ =====================\n\n";

    for (int i = 0; i < n; i++) {
        std::cout << "Sender sends Frame " << i + 1 << " (Data: " << frames[i] << ")\n";

        // Every 3rd frame is lost (Frame 3, 6, 9...)
        if ((i + 1) % 3 == 0) {
            std::cout << "  [!] Frame " << i + 1 << " lost during transmission!\n";
            std::cout << "  [!] Timeout! Sender waiting for ACK...\n";
            std::cout << "Sender retransmits Frame " << i + 1 << " (Data: " << frames[i] << ")\n";
        }

        // Receiver successfully receives the frame
        std::cout << "Receiver received Frame " << i + 1 << " with Data: " << frames[i] << "\n";
        
        // Receiver sends ACK back to Sender
        std::cout << "Receiver sends ACK " << i + 1 << "\n";
        std::cout << "Sender received ACK " << i + 1 << "\n\n";
    }

    return 0;
}
