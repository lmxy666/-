#include "advancedai.h"
void chessai::init(Chess* chess)
{
    this->chess = chess;

    for (int i = 0; i < chess->getSize(); i++)
    {
        vector<int> row;
        for (int j = 0; j < chess->getSize(); j++)
        {
            row.push_back(0);
        }

        scoreMap.push_back(row);
    }
}
void chessai::copyBoard(vector<vector<int>> A, int B[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE]) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (A[i][j] == C_NONE)B[i][j] = C_NONE;
            else if (A[i][j] == C_BLACK)B[i][j] = C_BLACK;
            else B[i][j] = C_WHITE;
        }
    }
}

ChessPos* chessai::get_best_move(int depth)
{
    int A[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE];
    copyBoard(chess->chessMap, A);
    int bestVal = INT_MIN;
    ChessPos chesspos; // �洢����λ��

    for (int i = 0; i < BOARD_GRAD_SIZE; i++) {
        for (int j = 0; j < BOARD_GRAD_SIZE; j++) {
            if (chess->is_valid_move(i, j)) {
                chess->make_move(i, j,A,white);  // AI����
                int moveVal = minimax(depth - 1, INT_MIN, INT_MAX, false);  // ��������岽
                chess->undo_move(i, j,A);  // �����岽
                if (moveVal > bestVal) {  // ��������岽
                    chesspos.row = i;
                    chesspos.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    ChessPos* pos = &chesspos;
    return pos;
}

void chessai::advancedgo()
{
    ChessPos* Pos = get_best_move(4);//�����������Ϊ4
    chess->Luozi(Pos, white);
}

int chessai::minimax(int depth, int alpha, int beta, bool isMaximizingPlayer)
{
    {
        int A[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE];
        // ����������������Ȼ���Ϸ��������������
        if (depth == 0) {
            EVALUATION eval = evaluate(A);  // ������������
            return eval.score;  // ���ص�ǰ���Ƶ�����
        }

        if (isMaximizingPlayer) {  // AI�Ļغϣ��������
            int maxEval = INT_MIN;
            for (int i = 0; i < BOARD_GRAD_SIZE; i++) {
                for (int j = 0; j < BOARD_GRAD_SIZE; j++) {
                    if (chess->is_valid_move(i, j)) {
                        chess->make_move(i, j, A,white);  // AI����
                        int eval = minimax(depth - 1, alpha, beta, false);  // �ݹ���ã��л�Ϊ���ֻغ�
                        chess->undo_move(i, j,A);  // �����岽
                        maxEval = max(maxEval, eval);
                        alpha = max(alpha, eval);  // ���� �� ֵ
                        if (beta <= alpha) break;  // ��-�¼�֦
                    }
                }
            }
            return maxEval;
        }
        else {  // ���ֵĻغϣ���С������
            int minEval = INT_MAX;
            for (int i = 0; i < BOARD_GRAD_SIZE; i++) {
                for (int j = 0; j < BOARD_GRAD_SIZE; j++) {
                    if (chess->is_valid_move(i, j)) {
                        chess->make_move(i, j, A,black);  // ��������
                        int eval = minimax(depth - 1, alpha, beta, true);  // �ݹ���ã��л�ΪAI�غ�
                        chess->undo_move(i, j,A);  // �����岽
                        minEval = min(minEval, eval);
                        beta = min(beta, eval);  // ���� �� ֵ
                        if (beta <= alpha) break;  // ��-�¼�֦
                    }
                }
            }
            return minEval;
        }
    }
}

void chessai::init_tuple6type()
{
    memset(tuple6type, 0, sizeof(tuple6type));//ȫ����Ϊ0
    //����5,aiӮ
    tuple6type[2][2][2][2][2][2] = WIN;
    tuple6type[2][2][2][2][2][0] = WIN;
    tuple6type[0][2][2][2][2][2] = WIN;
    tuple6type[2][2][2][2][2][1] = WIN;
    tuple6type[1][2][2][2][2][2] = WIN;
    tuple6type[3][2][2][2][2][2] = WIN;//�߽翼��
    tuple6type[2][2][2][2][2][3] = WIN;
    //����5,ai��
    tuple6type[1][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][0] = LOSE;
    tuple6type[0][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][2] = LOSE;
    tuple6type[2][1][1][1][1][1] = LOSE;
    tuple6type[3][1][1][1][1][1] = LOSE;
    tuple6type[1][1][1][1][1][3] = LOSE;
    //�׻�4
    tuple6type[0][2][2][2][2][0] = FLEX4;
    //�ڻ�4
    tuple6type[0][1][1][1][1][0] = flex4;
    //�׻�3
    tuple6type[0][2][2][2][0][0] = FLEX3;
    tuple6type[0][0][2][2][2][0] = FLEX3;
    tuple6type[0][2][0][2][2][0] = FLEX3;
    tuple6type[0][2][2][0][2][0] = FLEX3;
    //�ڻ�3
    tuple6type[0][1][1][1][0][0] = flex3;
    tuple6type[0][0][1][1][1][0] = flex3;
    tuple6type[0][1][0][1][1][0] = flex3;
    tuple6type[0][1][1][0][1][0] = flex3;
    //�׻�2
    tuple6type[0][2][2][0][0][0] = FLEX2;
    tuple6type[0][2][0][2][0][0] = FLEX2;
    tuple6type[0][2][0][0][2][0] = FLEX2;
    tuple6type[0][0][2][2][0][0] = FLEX2;
    tuple6type[0][0][2][0][2][0] = FLEX2;
    tuple6type[0][0][0][2][2][0] = FLEX2;
    //�ڻ�2
    tuple6type[0][1][1][0][0][0] = flex2;
    tuple6type[0][1][0][1][0][0] = flex2;
    tuple6type[0][1][0][0][1][0] = flex2;
    tuple6type[0][0][1][1][0][0] = flex2;
    tuple6type[0][0][1][0][1][0] = flex2;
    tuple6type[0][0][0][1][1][0] = flex2;
    //�׻�1
    tuple6type[0][2][0][0][0][0] = FLEX1;
    tuple6type[0][0][2][0][0][0] = FLEX1;
    tuple6type[0][0][0][2][0][0] = FLEX1;
    tuple6type[0][0][0][0][2][0] = FLEX1;
    //�ڻ�1
    tuple6type[0][1][0][0][0][0] = flex1;
    tuple6type[0][0][1][0][0][0] = flex1;
    tuple6type[0][0][0][1][0][0] = flex1;
    tuple6type[0][0][0][0][1][0] = flex1;

    int p1, p2, p3, p4, p5, p6, x, y, ix, iy;//x:��5�кڸ���,y:��5�а׸���,ix:��5�кڸ���,iy:��5�а׸���
    for (p1 = 0; p1 < 4; ++p1) {

        for (p2 = 0; p2 < 3; ++p2) {

            for (p3 = 0; p3 < 3; ++p3) {

                for (p4 = 0; p4 < 3; ++p4) {

                    for (p5 = 0; p5 < 3; ++p5) {

                        for (p6 = 0; p6 < 4; ++p6) {

                            x = y = ix = iy = 0;

                            if (p1 == 1)x++;
                            else if (p1 == 2)y++;

                            if (p2 == 1) {
                                x++; ix++;
                            }
                            else if (p2 == 2) {
                                y++; iy++;
                            }

                            if (p3 == 1) {
                                x++; ix++;
                            }
                            else if (p3 == 2) {
                                y++; iy++;
                            }

                            if (p4 == 1) {
                                x++; ix++;
                            }
                            else if (p4 == 2) {
                                y++; iy++;
                            }

                            if (p5 == 1) {
                                x++; ix++;
                            }
                            else if (p5 == 2) {
                                y++; iy++;
                            }

                            if (p6 == 1)ix++;
                            else if (p6 == 2)iy++;

                            if (p1 == 3 || p6 == 3) {
                                //�б߽�
                                if (p1 == 3 && p6 != 3) {
                                    //��߽�
                                                            //�׳�4
                                    if (ix == 0 && iy == 4) {
                                        //���ұ��п�λ�ǻ�4Ҳû��ϵ����Ϊ��4Ȩ��Զ���ڳ�4���ټ��ϳ�4Ȩ�ر仯���Բ���
                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //�ڳ�4
                                    if (ix == 4 && iy == 0) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //����3
                                    if (ix == 0 && iy == 3) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //����3
                                    if (ix == 3 && iy == 0) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //����2
                                    if (ix == 0 && iy == 2) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //����2
                                    if (ix == 2 && iy == 0) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                                else if (p6 == 3 && p1 != 3) {
                                    //�ұ߽�
                                                            //�׳�4
                                    if (x == 0 && y == 4) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                    }
                                    //�ڳ�4
                                    if (x == 4 && y == 0) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                    }
                                    //����3
                                    if (x == 3 && y == 0) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                    }
                                    //����3
                                    if (x == 0 && y == 3) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                    }
                                    //����2
                                    if (x == 2 && y == 0) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                    }
                                    //����2
                                    if (x == 0 && y == 2) {

                                        if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                            tuple6type[p1][p2][p3][p4][p5][p6] = block2;
                                    }
                                }
                            }
                            else {
                                //�ޱ߽�
                                                    //�׳�4
                                if ((x == 0 && y == 4) || (ix == 0 && iy == 4)) {

                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK4;
                                }
                                //�ڳ�4
                                if ((x == 4 && y == 0) || (ix == 4 && iy == 0)) {

                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = block4;
                                }
                                //����3
                                if ((x == 0 && y == 3) || (ix == 0 && iy == 3)) {

                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK3;
                                }
                                //����3
                                if ((x == 3 && y == 0) || (ix == 3 && iy == 0)) {

                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = block3;
                                }
                                //����2
                                if ((x == 0 && y == 2) || (ix == 0 && iy == 2)) {

                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = BLOCK2;
                                }
                                //����2
                                if ((x == 2 && y == 0) || (ix == 2 && iy == 0)) {

                                    if (tuple6type[p1][p2][p3][p4][p5][p6] == 0)
                                        tuple6type[p1][p2][p3][p4][p5][p6] = block2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

EVALUATION chessai::evaluate(int board[BOARD_GRAD_SIZE][BOARD_GRAD_SIZE])
{
    init_tuple6type();
    //������Ȩ��
    int weight[17] = { 0,1000000,-10000000,50000,-100000,400,-100000,400,-8000,20,-50,20,-50,1,-3,1,-3 };

    int i, j, type;
    int stat[4][17];//ͳ��4��������ÿ�����͵ĸ���
    memset(stat, 0, sizeof(stat));


    int A[17][17];//�����߽�����������,board[i][j]=A[i-1][j-1],3��ʾ�߽�
    for (int i = 0; i < 17; ++i)A[i][0] = 3;
    for (int i = 0; i < 17; ++i)A[i][16] = 3;
    for (int j = 0; j < 17; ++j)A[0][j] = 3;
    for (int j = 0; j < 17; ++j)A[16][j] = 3;
    for (int i = 0; i < 15; ++i)
        for (int j = 0; j < 15; ++j)
            A[i + 1][j + 1] = board[i][j];

    //�жϺ�������
    for (i = 1; i <= 15; ++i) {
        for (j = 0; j < 12; ++j) {
            type = tuple6type[A[i][j]][A[i][j + 1]][A[i][j + 2]][A[i][j + 3]][A[i][j + 4]][A[i][j + 5]];
            stat[0][type]++;
        }
    }
    //�ж���������
    for (j = 1; j <= 15; ++j) {
        for (i = 0; i < 12; ++i) {
            type = tuple6type[A[i][j]][A[i + 1][j]][A[i + 2][j]][A[i + 3][j]][A[i + 4][j]][A[i + 5][j]];
            stat[1][type]++;
        }
    }
    //�ж���������������
    for (i = 0; i < 12; ++i) {
        for (j = 0; j < 12; ++j) {
            type = tuple6type[A[i][j]][A[i + 1][j + 1]][A[i + 2][j + 2]][A[i + 3][j + 3]][A[i + 4][j + 4]][A[i + 5][j + 5]];
            stat[2][type]++;
        }
    }
    //�ж���������������
    for (i = 0; i < 12; ++i) {
        for (j = 5; j < 17; ++j) {
            type = tuple6type[A[i][j]][A[i + 1][j - 1]][A[i + 2][j - 2]][A[i + 3][j - 3]][A[i + 4][j - 4]][A[i + 5][j - 5]];
            stat[3][type]++;
        }
    }

    EVALUATION eval;
    memset(eval.STAT, 0, sizeof(eval.STAT));

    int score = 0;
    for (i = 1; i < 17; ++i) {
        score += (stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i]) * weight[i];//�����Ʒ�

        int count = stat[0][i] + stat[1][i] + stat[2][i] + stat[3][i];//ͳ�����з����ϲ������͵ĸ���
        if (i == WIN)eval.STAT[WIN] = count;
        else if (i == LOSE)eval.STAT[LOSE] = count;
        else if (i == FLEX4)eval.STAT[FLEX4] = count;
        else if (i == BLOCK4)eval.STAT[BLOCK4] = count;
        else if (i == FLEX3)eval.STAT[FLEX3] = count;
    }

    eval.result = R_DRAW;

    //��Ӯ
    if (eval.STAT[WIN] > 0)eval.result = R_WHITE;
    //��Ӯ
    else if (eval.STAT[LOSE] > 0)eval.result = R_BLACK;

    eval.score = score;
    return eval;
}

