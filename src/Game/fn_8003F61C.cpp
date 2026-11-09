// Steps the active record of one actor id for the Replay state's update.

struct Rec;

extern int lbl_8066B7A0;

extern "C" {
Rec *fn_80046AC8(int handle);
int fn_8003F6C8(Rec *rec);
int fn_80046050(Rec *rec);

int fn_8003F61C(int handle)
{
    Rec *rec = fn_80046AC8(handle);
    if (rec) {
        switch (lbl_8066B7A0) {
        case 3:
            return fn_8003F6C8(rec);
            break;
        case 4:
        case 5:
        case 6:
            return fn_80046050(rec);
            break;
        }
    }
    return 0;
}
}
