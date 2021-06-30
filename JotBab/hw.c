#include <cstdio>
#include <cstdlib>      // rand() �Լ��� ����
#include <ctime>        // time() �Լ��� ����
extern double tElapsed;   // ���� �ҿ� �ð�
extern double playSpeedGugu(int nPlay);



static int NumGames = 0;   // ��ü �õ� Ƚ��
static int NumWins = 0;   // ���� Ƚ��
static double Score = 0;   // ����
double tElapsed = 0;       // ���� �ҿ�ð�

double playSpeedGames(int nPlay, int gameNum, int nDigit = 0)
{
    clock_t   t0 = clock();
    for (int i = 0; i < nPlay; i++) {
        if (gameNum == 1) {
            if (playGuguOnce() == false)
                printf("\tƲ�Ƚ��ϴ�.\n");
        }
        else if (gameNum == 2) {
            if (playMultOnce() == false)
                printf("\tƲ�Ƚ��ϴ�.\n");
        }
        else if (3 <= gameNum && gameNum <= 9) {
            if (playPlusOnce(nDigit) == false)
                printf("\tƲ�Ƚ��ϴ�.\n");
        }
    }
    clock_t   t1 = clock();
    tElapsed = (double)(t1 - t0) / CLOCKS_PER_SEC;
    Score = (NumGames > NumWins) ? 0.0
        : 100 * (5.0 * NumGames - tElapsed) / (5.0 * NumGames);
    return Score;
}

static bool playGuguOnce()
{
    int   a = rand() % 8 + 2;
    int   b = rand() % 8 + 2;
    int   result;

    NumGames++;
    printf("[����%2d]: %2d x %2d = ", NumGames, a, b);
    scanf_s("%d", &result);
    if (result == a * b) NumWins++;
    return (result == a * b);
}

static bool playPlusOnce(int nDigits)
{
    int start = pow(10.0, (double)nDigits - 1); 
    int end = pow(10.0, (double)nDigits) - 1;

    int a = rand() % (end + 1 - start) + start;
    int b = rand() % (end + 1 - start) + start;
    
    int   result;

    NumGames++;
    printf("[����%2d]:\t%d\t+\t%d\t= ", NumGames, a, b);
    scanf_s("%d", &result);
    if (result == a + b) NumWins++;
    return (result == a + b);
}

static bool playMultOnce()
{
    int start = 10;
    int end = 99;
    int a = rand() % (end + 1 - start) + start;
    int b = rand() % (end + 1 - start) + start;

    int   result;

    NumGames++;
    printf("[����%2d]: %2d x %2d = ", NumGames, a, b);
    scanf_s("%d", &result);
    if (result == a * b) NumWins++;
    return (result == a * b);
}

void init() {
    NumGames = 0;   // ��ü �õ� Ƚ�� �ʱ�ȭ
    NumWins = 0;   // ���� Ƚ�� �ʱ�ȭ
    Score = 0;   // ���� �ʱ�ȭ
    tElapsed = 0;       // ���� �ҿ�ð� �ʱ�ȭ
}

void main()
{
    srand((unsigned)time(NULL));

    int nPlay = 10;
    printf("[���ǵ� ������ ����]\n\n");
    printf(" ����� ������ �Ƿ��� �׽�Ʈ�ϼ���.!!!\n");
    printf(" %d�� �׽�Ʈ �ϰڽ��ϴ�.\n", nPlay);
    printf(" ũ�� ��ȣ���� �Ͻð�...\n �غ�Ǹ� ���͸� ��������...");
    getchar();
    system("cls");

    double score = playSpeedMult(nPlay);
    printf("\n���� = %4.1f��(�� %4.1f��)\n", score, tElapsed);
}