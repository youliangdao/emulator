#include <stdint.h>
#include "emulator.h"

/* ModR/Mを表す構造体 */
typedef struct
{
  uint8_t mod;

   /* opecodeとreg_indexは別名で同じ物 */
  union
  {
    uint8_t opecode;
    uint8_t reg_index;
  };
  uint8_t rm;

  /* SIB が必要な mod/rm の組み合わせの時に使う */
  uint8_t sib;
  union
  {
    int8_t disp8; // disp8 は符号付き整数
    uint32_t disp32;
  };
} ModRM;

/* ModR/M, SIB, ディスプレースメントを解析する
 *
 * emu から ModR/M, SIB, ディスプレースメントを読み取って modrm にセットする。
 * 呼び出しのとき emu->eip は ModR/M バイトを指している必要がある。
 * この関数は emu->eip を即値（即値がない場合は次の命令）の先頭を指すように変更する。
 *
 * 引数
 *   emu: eip が ModR/M バイトの先頭を指しているエミュレータ構造体
 *   modrm: 解析結果を格納する構造体
 */
void parse_modrm(Emulator* emu, ModRM* modrm);

/*rm32のレジスタまたはメモリの32bit値を設定する
・＊
・＊・modrmの内容にしたがってvalueを目的のメモリまたはレジスタに書き込む
・＊
・＊引数
・＊・・・emu:エミュレータ構造体（eipはどこを指しても良い）
・＊・・・modrm:ModR/M(SIB,dispを含む)
・＊・・・value：即値
*/
void set_rm32(Emulator* emu, ModRM* modrm, uint32_t value);

/*・ModR/M・の内容に基づきメモリの実行アドレスを計算する
・＊
・＊・modrm->mod・は0,1,2もいずれかでなければならない
*/
uint32_t calc_memory_address(Emulator* emu, ModRM* modrm);

