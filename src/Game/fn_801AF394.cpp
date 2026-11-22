// Frame clock lbl_80593BE8 (docs/core.md row 14, section 4.8).
// Owns the .rodata pools 0x8049E308-0x8049E350; the file's unread tail stays with dtk.

struct OSCalendarTime
{
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
};

struct ClockCounter
{
    int frames;
    int ms;
    float sec;
    unsigned int dms;
    float dsec;
    float fps;
    float scale;
    int paused;
};

struct Clock
{
    int started;
    int frames;
    int time;
    int delta;
    int step;
    float scale;
    long long last;
    ClockCounter real;
    ClockCounter game; // +0x40
    float target;      // +0x60
    float rate;
    int fixed;
    float fixedDt;
};

struct ClockDate
{
    unsigned short month;
    unsigned short day;
    unsigned short year;
    unsigned short hour;
    unsigned short min;
    unsigned short sec;
    unsigned int stamp;
};

extern "C" {
long long OSGetTime(void);
void OSTicksToCalendarTime(long long ticks, OSCalendarTime *ct);
int fn_8023D994(int hz);
int fn_8023EA4C(void);
float fn_8042CE28(int x);
void fn_8046697C(Clock *self, int time);
float fn_804669A4(Clock *self);
int fn_804669D0(Clock *self);
int fn_804439A4(Clock *self);
float fn_80435650(Clock *self);
void fn_801AA368(void);

Clock *fn_801AF394(register Clock *self);
void fn_801AF3D4(register Clock *self);
void fn_801AF60C(register Clock *self);
void fn_801AF668(register Clock *self);

Clock lbl_80593BE8;

Clock *fn_801AF394(register Clock *self)
{
    fn_801AF3D4(self);
    return self;
}

void fn_801AF3D4(register Clock *self)
{
    self->started = 0;
    self->frames = 0;
    self->time = 0;
    self->step = 0;
    fn_801AF60C(self);
    self->real.scale = 1.0f;
    self->real.paused = 0;
    fn_801AF668(self);
    self->game.scale = 1.0f;
    self->target = 1.0f;
    self->game.paused = 0;
    if (!fn_8023D994(1000)) {
    }
    self->scale = 1.0f;
    self->last = fn_8023EA4C();
    self->time = (int)(fn_8042CE28(self->last) * self->scale);
    self->fixed = 0;
}

void fn_801AF4CC(register Clock *self, ClockDate *out)
{
    OSCalendarTime ct;
    long long t = OSGetTime();
    OSTicksToCalendarTime(t, &ct);
    out->sec = ct.sec;
    out->min = ct.min;
    out->hour = ct.hour;
    out->day = ct.mday;
    out->month = ct.mon + 1;
    out->year = ct.year;
    out->stamp = out->sec + out->min * 60 + out->hour * 3600 + out->day * 86400 + out->month * 2678400
               + (out->year - 2000) * 31536000;
}

void fn_801AF60C(register Clock *self)
{
    self->real.frames = 0;
    self->real.ms = 0;
    self->real.sec = 0.0f;
    self->real.dms = 0;
    self->real.dsec = 0.0f;
    self->real.fps = 0.1f;
}

void fn_801AF668(register Clock *self)
{
    self->game.frames = 0;
    self->game.ms = 0;
    self->game.sec = 0.0f;
    self->game.dms = 0;
    self->game.dsec = 0.0f;
    self->game.fps = 0.1f;
}

void fn_801AF6C4(register Clock *self)
{
    fn_801AF3D4(self);
    fn_8046697C(&lbl_80593BE8, fn_8023EA4C());
    self->started = 1;
}

void fn_801AF71C(register Clock *self)
{
    fn_801AF668(self);
}

void fn_801AF754(register Clock *self)
{
    fn_801AA368();
    self->game.paused = 1;
}

void fn_801AF790(register Clock *self)
{
    unsigned int now;
    unsigned int elapsed;
    float dt;

    self->frames++;
    now = fn_8023EA4C();
    if (self->last > now) {
        elapsed = now;
    } else {
        elapsed = now - self->last;
    }
    self->last = now;
    if (self->step != 0) {
        elapsed = (int)(fn_8042CE28(self->step) / self->scale);
    }
    self->time = (int)((float)now * self->scale);

    if (!fn_804669D0(self)) {
        self->real.frames++;
        if (self->fixed) {
            self->real.dms = (int)(self->fixedDt * 1000.0f);
        } else {
            self->real.dms = (float)elapsed * self->scale * fn_804669A4(self);
        }
        self->delta = self->real.dms;
        self->real.dms = self->real.dms ? (self->real.dms > 1000 ? 1000 : self->real.dms) : 1;
        self->real.ms += self->real.dms;
        self->real.sec = fn_8042CE28(self->real.ms) * 0.001f;
        self->real.dsec = fn_8042CE28(self->real.dms) * 0.001f;
        self->real.fps = 1.0f / self->real.dsec;
    } else {
        self->real.dms = 0;
        self->real.dsec = 0.0f;
        self->real.fps = 0.0f;
    }

    if (self->game.scale != self->target) {
        self->game.scale = self->game.scale < self->target
                               ? (self->rate * self->real.dsec + self->game.scale > self->target
                                      ? self->target
                                      : self->game.scale + self->rate * self->real.dsec)
                               : (self->game.scale - self->rate * self->real.dsec < self->target
                                      ? self->target
                                      : self->game.scale - self->rate * self->real.dsec);
    }

    if (!fn_804439A4(self)) {
        self->game.frames++;
        if (self->fixed) {
            dt = self->fixedDt * 1000.0f;
        } else {
            dt = fn_8042CE28(elapsed) * self->scale;
        }
        dt = dt >= 1.0f ? (dt <= 1000.0f ? dt : 1000.0f) : 1.0f;
        dt *= fn_80435650(self);
        self->game.dms = (int)dt;
        self->game.dsec = dt * 0.001f;
        self->game.sec += self->game.dsec;
        self->game.ms = (int)(self->game.sec * 1000.0f);
        self->game.fps = 1.0f / self->game.dsec;
    } else {
        self->game.dms = 0;
        self->game.dsec = 0.0f;
        self->game.fps = 0.0f;
    }
}

__asm__(".section .rodata\n\t.float 0.0\n\t.text"); // orphan at 0x8049E344

float fn_801AFC50(register Clock *self, float scale, float time)
{
    float old = self->game.scale;
    if (time <= 0.0f) {
        self->game.scale = scale > 0.0f ? scale : 0.0f;
        self->target = self->game.scale;
    } else {
        self->target = scale > 0.0f ? scale : 0.0f;
        self->rate = 1.0f / time;
    }
    return old;
}

void fn_801AFD14(unsigned int ms, unsigned int *h, unsigned int *m, unsigned int *s, unsigned int *msOut)
{
    unsigned int secs;
    unsigned int mins;

    *msOut = ms % 1000;
    secs = (ms - *msOut) / 1000;
    *s = secs % 60;
    mins = (secs - *s) / 60;
    *m = mins % 60;
    *h = (mins - *m) / 60;
}
}

static void __static_initialization_and_destruction_0(int initialize, int priority)
{
    if (priority == 65535) {
        if (initialize) {
            fn_801AF394(&lbl_80593BE8);
        } else {
        }
    }
}

extern "C" {
void fn_801AFE84(void)
{
    __static_initialization_and_destruction_0(1, 65535);
}

static void (*const sCtorEntry)(void) __attribute__((section(".ctors"))) = fn_801AFE84;
}
