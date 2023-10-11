#include <stdlib.h>

int main() {
    const char* timezone = "America/New_York"; // Replace with the desired timezone

    // Set the timezone using the TZ environment variable
    setenv("TZ", timezone, 1);
    tzset();

    // Test by printing the current time
    system("date");

    return 0;
}
