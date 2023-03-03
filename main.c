#include <stdio.h>
#define ID_LENG 24

// 適当に書いたので暇があったら書き換える

/**
 * @brief ファイルからsmやncから始めるものを書き出す。
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const *argv[])
{
    // ファイル
    FILE *fp;

    // id
    char nico_id[ID_LENG];
    // id画指し示す位置
    unsigned int id_target = 0;

    // idの先頭の文字
    char *id_head[] = {"im", "nc", "sm"};
    // idの種類
    int id_leng = 3;
    // idの種類
    int id_type = 0;
    // ファイルから読み込んだ文字
    char get_char;

    // 引数が二個以下なら動かない
    if (argc < 2)
    {
        printf("arg error\n");
        return -1;
    }

    // 入れられたファイルの数だけする
    for (int file_index = 1; file_index < argc; file_index++)
    {
        // ファイルを開く
        if ((fp = fopen(argv[file_index], "r")) == NULL)
        {
            printf("fopen error\n");
            return -1;
        }
        printf("%s\n", argv[file_index]);
        // 1文字ずつ読み込む
        while ((get_char = fgetc(fp)) != EOF)
        {
            if (id_target == 1)
            {
                if (get_char == id_head[id_type][id_target])
                {
                    nico_id[id_target++] = get_char;
                }
                else
                {
                    id_target = 0;
                }
            }
            else if (2 <= id_target)
            {
                if ('0' <= get_char && get_char <= '9')
                {
                    nico_id[id_target++] = get_char;
                }
                else
                {
                    // ファイルの拡張子直前の.があればそれがnico_idと断定(多分重複あるけどいいや)
                    if (get_char == '.')
                    {
                        nico_id[id_target++] = '\n';
                        nico_id[id_target] = 0;
                        printf("%s", nico_id);
                    }
                    id_target = 0;
                }
            }
            // これは最後にする
            // idを推測する
            if (id_target == 0)
            {
                for (id_type = 0; id_type < id_leng; id_type++)
                {
                    if (get_char == id_head[id_type][id_target])
                    {
                        nico_id[id_target++] = get_char;
                        break;
                    }
                }
            }
        }
        printf("\n");
        fclose(fp);
    }
    return 0;
}
