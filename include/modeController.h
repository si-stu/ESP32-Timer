#ifndef MODECONTROLLER_H
#define MODECONTROLLER_H

enum class Mode {
    INIT,
    STANDBY,
    TIMER,
    TEST
};

class ModeController {
public:
    ModeController();
    ~ModeController();
    bool setMode(Mode newMode);

private:
    Mode mode;

    // Private methods
    Mode getMode() const;
};

#endif