// BaseF destructor: forwards to the root's with the in-charge flag (docs/versus.md section 5). Names are guesses.
extern void fn_8042A780(void *self, int a);

void fn_8045F410(register void *self, register int inChrg)
{
    fn_8042A780(self, inChrg);
}
