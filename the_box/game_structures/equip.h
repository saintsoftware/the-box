
// ========== DECLARATION =================

/* IN Variables */

int slots = 0;

class TrollCarriedItem
{
 public:
  TrollCarriedItem(IUShort num, IUShort slt, IUShort str);
  virtual ~TrollCarriedItem();
  virtual void activate(TrollCharacter *troll, TrollScreen *screen) = 0;
  virtual void draw(IScreen drawscreen, IUShort x, IUShort y);
  IUShort getItemNum();
  IUShort getSlot();
  IUShort getStrength();
  IUShort getSprite();
  IUShort getShift();
  virtual void read(BinaryReadFile &f);
  virtual void write(BinaryWriteFile &f);

 protected:
  IUShort itemNum;
  IUShort slot;
  IUShort strength;
  IUShort sprite;
  IUShort shift;
};
