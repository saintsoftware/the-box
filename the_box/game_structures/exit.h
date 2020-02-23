
// ========== Inherit =================

/*
Level

*/

// ========== DECLARATION =================

/* IN Variables */


TrollExit(BinaryReadFile &f);
TrollExit(IUShort ex, IUShort ey, const char *lvlNm = NULL,
IUShort nsx = 0, IUShort nsy = 0, IUShort nx = 0, IUShort ny = 0);
~TrollExit();
IUShort getX() const;
IUShort getY() const;
const char *getLevelName() const;
IUShort getNewScreenX() const;
IUShort getNewScreenY() const;
IUShort getNewX() const;
IUShort getNewY() const;
void setX(IUShort val);
void setY(IUShort val);
void setLevelName(const char *val);
void setNewScreenX(IUShort val);
void setNewScreenY(IUShort val);
void setNewX(IUShort val);
void setNewY(IUShort val);
void write(BinaryWriteFile &f);

IUShort x, y;
char *levelName;
IUShort newScreenX, newScreenY;
IUShort newX, newY;
