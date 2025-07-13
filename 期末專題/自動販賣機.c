//
//  main.c
//  模擬自動販賣機
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITEM_COUNT 12 // 商品數量
#define Length 59
#define MAX_RESTOCK_RECORDS 50 // 最大補貨紀錄數量

//商品結構體
typedef struct {
    char name[20];
    int price;
    int stock;
} Item;

typedef struct {
    char name[20];
    int history[ITEM_COUNT];
} User;

typedef struct {
    char itemName[20];
    int quantity;
} RestockRecord;


// 檔案名稱
#define INVENTORY_FILE "inventory.txt"
#define RESTOCK_FILE "restock_records.txt"
#define PURCHASE_FILE "purchase_records.txt"

//商品清單
Item items[ITEM_COUNT] = {
    {"麥香紅茶", 40, 10}, {"寶礦力水得", 40, 8}, {"可樂", 25, 5},
    {"麥香奶茶", 35, 6}, {"三合一咖啡", 40, 7}, {"雪碧", 25, 4},
    {"麥香綠茶", 50, 3}, {"無糖黑咖啡", 25, 2}, {"舒跑", 20, 6},
    {"純喫綠茶", 15, 8}, {"保利達蠻牛", 25, 5}, {"麥茶", 30, 7}
};

// 使用者清單 (動態陣列)
User *users = NULL; // 初始為 NULL
int userCount = 0;  // 當前使用者數量

// 補貨紀錄
RestockRecord restockRecords[MAX_RESTOCK_RECORDS];
int restockCount = 0; // 當前補貨紀錄數量

//函數宣告
void trimNewline(char *str); //移除換行
void viewPurchaseRecordsByAdmin(void); // 管理者查詢某帳號購買紀錄
void viewPurchaseRecordsByUser(const char *account); //購買者查看購買紀錄
void loadInventory(void); //讀取或新增庫存的txt
void saveInventory(void); //儲存庫存進入txt
void loadRestockRecords(void); //讀取補貨紀錄
void saveRestockRecords(void); //儲存補貨紀錄進入txt
void savePurchaseRecord(const char *userName, const char *itemName, int quantity); //儲存購買紀錄進入txt
void displayMachine(void);  //顯示販賣機外觀
void restockItems(void);    //管理員補貨
void addRestockRecord(const char *itemName, int quantity); //新增補貨紀錄
void viewStock(void);         // 查看庫存
void viewRestockRecords(void); // 查看補貨紀錄
void purchaseItem(const char *account);    //購買商品
void processPurchase(User *user);  //處理購買
void login(void);           //登入系統
User *findOrAddUser(const char *name); //尋找或新增使用者
void printUserHistory(const User *user); //列印使用者購買紀錄
void recommendItem(User *user) ;
void viewAllPurchaseRecordsByAdmin(void);

//主程式
int main(void) {
    srand(time(NULL)); // 初始化亂數種子
    printf("叮咚！\n");
    printf("歡迎使用C販賣機C\n");

    // 啟動時讀取檔案
    loadInventory();
    loadRestockRecords();

    while (1) {
        login();
    }

    // 結束前保存檔案
    saveInventory();
    saveRestockRecords();

    free(users); // 程式結束前釋放記憶體
    return 0;
}

void displayMachine(void) {

    for(int i=0;i<Length;i++) printf("-");
    printf("\n");

    //顯示販賣機名稱
    int titlePadding= (Length-9)/2;
    for(int i=0;i<titlePadding;i++) printf(" ");
    printf("c販賣機c\n");

    //顯示分隔線
    for(int i=0;i<Length;i++) printf("=");
    printf("\n");

    //顯示商品
    FILE *file = fopen(INVENTORY_FILE, "r");
    printf("商品編號\t商品名稱\t價格\t庫存\n");
    printf("------------------------------------------\n");

    if (!file) {
        viewStock();
        //顯示分隔線
        for(int i=0;i<Length-10;i++) printf("=");
        printf("\n");

        //顯示取貨口＆明細出口
        printf("       取貨口                        明細出口\n");
        printf(" |-----------------|            ---------------\n");
        printf(" |                 |           |               |\n");
        printf(" |                 |           |               |\n");
        printf(" |                 |            ---------------\n");
        printf(" |-----------------|                             \n");

        printf("\n");
        for(int i=0;i<Length-10;i++) printf("-");
        printf("\n");
            return;
    }

    printf("\n目前販賣機商品清單：\n");
    char name[20];
    int price, stock;

    for (int i = 0; i < ITEM_COUNT; i++) {
        if (fscanf(file, "%s %d %d", name, &price, &stock) != 3) {
            printf("讀取商品資料時發生錯誤！第 %d 筆資料格式有誤。\n", i + 1);
            continue;
        }
        printf("  %2d\t\t%-15s\t$%-4d\t%-2d\n", i + 1, name, price, stock);
    }

    fclose(file);

    //顯示分隔線
    for(int i=0;i<Length;i++) printf("=");
    printf("\n");

    //顯示取貨口＆明細出口
    printf("         取貨口                               明細出口\n");
    printf(" |--------------------|               --------------------\n");
    printf(" |                    |               |                  |\n");
    printf(" |                    |               |                  |\n");
    printf(" |                    |               --------------------\n");
    printf(" |--------------------|                                  \n");

    printf("\n");
    for(int i=0;i<Length;i++) printf("-");
    printf("\n");
}

//管理者
void restockItems(void){
    printf("\n您已經進入到管理者介面\n");
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (items[i].stock == 0) {
            printf("商品 %s 庫存為 0，請補貨\n", items[i].name);
        }
    }

    int option, choice;
    do {
        printf("\n請選擇操作: 1=補充商品, 2=查看庫存, 3=查看補貨紀錄, 4=查詢某帳號購買紀錄, 5=查詢所有購買紀錄, 0=退出\n");
        scanf("%d", &option);

        switch (option) {
            case 1: {

                int productID, quantity;
                FOUND:   //跳回選擇
                printf("請選擇需要補貨的商品編號 (1-%d): ", ITEM_COUNT);
                scanf("%d", &productID);

                if (productID < 1 || productID > ITEM_COUNT ||(int)productID != productID) {
                    while(getchar() != '\n');
                    printf("無效商品編號！請輸入 1-%d 之間的數字。\n", ITEM_COUNT);

                    while (1) {
                        printf("1=重新輸入, 0=退出此功能: ");
                        if (scanf("%d", &choice) != 1) {
                            // 如果用戶輸入非整數，清除輸入緩衝區
                            while(getchar() != '\n');
                            printf("無效選項，請重新輸入。\n");
                        } else if (choice == 0 ) {
                            break; // 跳出循環
                        } else if (choice == 1) {
                            printf("\n");
                            goto FOUND; // 重新執行
                        } else {
                            printf("無效選項，請重新輸入。\n");
                        }
                    }

                    break;
                }

                FOUNDstock:
                printf("請輸入補貨數量: ");
                scanf("%d", &quantity);

                while (1) {
                    if (quantity >= 1) {
                        break;
                    }else if( (int)quantity != quantity) {
                        // 如果用戶輸入非整數，清除輸入緩衝區
                        while(getchar() != '\n');
                        printf("無效選項，請重新輸入。\n");
                        goto FOUNDstock;
                    }else if (quantity <= 0 ){
                        printf("補貨數量要大於0!\n");
                        goto FOUNDstock;// 結束*/
                    }
                    }



                int index = productID - 1;
                items[index].stock += quantity;
                printf("成功補貨 %d 件 %s！目前庫存：%d 件。\n", quantity, items[index].name, items[index].stock);


                saveInventory();
                addRestockRecord(items[index].name, quantity);
                break;
            }
            case 2:
                viewStock();
                break;
            case 3:
                viewRestockRecords();
                break;
            case 4:
                viewPurchaseRecordsByAdmin();
                break;
            case 5:
                viewAllPurchaseRecordsByAdmin();
                break;
            case 0:
                printf("退出管理者介面，感謝您的使用！\n");
                break;
            default:
                printf("無效操作！請重新輸入。\n");
        }
    } while (option != 0);
}
//購買者
void purchaseItem(const char *account) {
    printf("\n您已經進入到購買者介面\n");
    User *user = findOrAddUser(account);
    // 此處可以添加購買邏輯，確認用戶已被成功新增或找到
    printf("歡迎 %s，您可以開始購買商品！\n", user->name);

    int option;
    do {
        printf("請選擇操作: 1=購買商品, 2=查看庫存, 3=查看購買紀錄, 4=推薦購買, 0=退出\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                processPurchase(user);
                break;
            case 2:
                viewStock();
                break;
            case 3:
                viewPurchaseRecordsByUser(account);
                break;
            case 4:
                recommendItem(user);
                break;
            case 0:
                printf("退出購買介面，感謝您的使用！\n");
                break;
            default:
                printf("無效操作！請重新輸入。\n\n");
        }
    } while (option != 0);
}

void processPurchase(User *user) {
    int productID, quantity, amountPaid, choice;

    FOUND2:
    printf("\n請輸入商品編號: ");
    scanf("%d", &productID);

    if (productID < 1 || productID > ITEM_COUNT) {
        printf("無效商品編號！\n");
        while (1)
        {
            printf("1=重新輸入, 0=退出此功能: ");
            if (scanf("%d", &choice) != 1) {
                // 如果用戶輸入非整數，清除輸入緩衝區
                while(getchar() != '\n');
                printf("無效選項，請重新輸入。\n");
            } else if (choice == 0 ) {
                printf("\n");
                break; // 跳出循環
            } else if (choice == 1) {
                printf("\n");
                goto FOUND2;// 重新執行
            } else {
                printf("無效選項，請重新輸入。\n");
            }
        }
        return;
    }

    printf("請輸入購買數量: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("購買數量必須大於 0！\n");
        return;
    }

    int index = productID - 1;

    if (items[index].stock < quantity) {
        printf("商品庫存不足！目前僅剩 %d 件。\n", items[index].stock);
        return;
    }

    int totalCost = items[index].price * quantity;
    do {
        printf("總價為 $%d，請輸入金額: ", totalCost);
        scanf("%d", &amountPaid);

        if (amountPaid < totalCost) {
            printf("金額不足！還需補足 $%d。\n", totalCost - amountPaid);
            totalCost=totalCost - amountPaid;
        }
    } while (amountPaid < totalCost);

    items[index].stock -= quantity;
    user->history[index] += quantity;

    printf("成功購買 %d 件 %s！\n", quantity, items[index].name);

    // 保存購買紀錄與更新庫存檔案
    savePurchaseRecord(user->name, items[index].name, quantity);
    saveInventory(); // 即時更新庫存

    if (amountPaid > totalCost) {
        printf("找零 $%d。\n", amountPaid - totalCost);
    }
}

void login(void) {
    char password[10];
    char account[20];
    int isAdmin = 0;
    int wrongCount = 0;

    while (wrongCount < 3) {
        printf("請輸入帳號: ");
        scanf("%s", account);
        printf("請輸入密碼: ");
        scanf("%s", password);

        if (strcmp(password, "NCKU") == 0) {
            isAdmin = 1;
            printf("管理者登入成功！\n");
            displayMachine();
            restockItems();
            break;
        } else if (strcmp(password, "0000") == 0) {
            printf("購買者登入成功！\n");
            displayMachine();
            purchaseItem(account);
            break;
        } else {
            wrongCount++;
            if (wrongCount < 3) {
                printf("密碼錯誤！請重新輸入。\n");
            } else {
                printf("此機台不開放給校外人士。\n");
                printf("若要購買請至警衛室洽詢相關購買事宜。\n");
                printf("感謝您的使用！程式即將退出。\n");
                exit(0);//輸入三次錯誤，程式結束。
            }
        }
    }

    // 登出或切換帳戶
    int option;
    do {
        printf("\n選擇操作: 1=切換帳戶, 0=退出程式\n");
        scanf("%d", &option);
        if (option == 1) {
            printf("切換帳戶...\n");
            return; // 回到主程式的登入流程
        } else if (option == 0) {
            printf("感謝您的使用！程式即將退出。\n");
            exit(0);
        } else {
            printf("無效選項，請重新輸入。\n");
        }
    } while (option != 1 && option != 0);
}

//購買記錄
void printUserHistory(const User *user) {
    printf("\n購買紀錄 - %s\n", user->name);
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (user->history[i] > 0) {
            printf("%3d | %s 購買數量: %d\n", i + 1, items[i].name, user->history[i]);
        }
    }
}

//推薦商品
void recommendItem(User *user) {
    int purchasedItems[ITEM_COUNT];
    int purchasedCount = 0;

    // 收集使用者購買過的商品索引
    for (int i = 0; i < ITEM_COUNT; i++) {
        if (user->history[i] > 0) {
            purchasedItems[purchasedCount++] = i;
        }
    }

    int recommendedIndex;
    if (purchasedCount > 0) {
        // 從購買過的商品中隨機推薦
        recommendedIndex = purchasedItems[rand() % purchasedCount];
    } else {
        // 隨機從全部商品中推薦
        recommendedIndex = rand() % ITEM_COUNT;
    }

    printf("\n推薦您購買: %s (價格: $%d, 庫存: %d)\n",
           items[recommendedIndex].name,
           items[recommendedIndex].price,
           items[recommendedIndex].stock);
    // 問使用者是否要購買
    char choice;
    printf("您想購買這項商品嗎？(y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        int quantity, Choice;
        FOUND4:
        printf("請輸入購買數量: ");
        scanf("%d", &quantity);

        // 檢查庫存
        if (quantity <= 0) {
            printf("購買數量必須大於 0！\n");
            while (1)
            {
                printf("1=重新輸入, 0=退出此功能: ");
                if (scanf("%d", &Choice) != 1) {
                    // 如果用戶輸入非整數，清除輸入緩衝區
                    while(getchar() != '\n');
                    printf("無效選項，請重新輸入。\n");
                } else if (Choice == 0 ) {
                    break; // 跳出循環
                } else if (Choice == 1) {
                    goto FOUND4;// 重新執行
                } else {
                    printf("無效選項，請重新輸入。\n");
                }
            }
        //
            return;
        }
        if (quantity > items[recommendedIndex].stock) {
            printf("商品庫存不足！目前僅剩 %d 件。\n", items[recommendedIndex].stock);
            return;
        }

        // 更新庫存與購買紀錄
        items[recommendedIndex].stock -= quantity;
        user->history[recommendedIndex] += quantity;

        printf("成功購買 %d 件 %s！\n", quantity, items[recommendedIndex].name);
    } else {
        printf("已退出推薦頁面。\n");
    }
}

void viewStock(void) {
    printf("\n商品庫存：\n");

    FILE *file = fopen(INVENTORY_FILE, "r");
    if (!file) {
        for (int i = 0; i < ITEM_COUNT; i++) {
            printf("  %2d\t\t%-15s\t$%-4d\t%-2d\n", i + 1, items[i].name, items[i].price, items[i].stock);
        }
        return;
    }

    // 讀取並顯示檔案內容
    char name[20];
    int price, stock;
    for (int i = 0; i < ITEM_COUNT; i++) {
        fscanf(file, "%s %d %d", name, &price, &stock);
        printf("%3d | %s 價格: $%d, 庫存: %d\n", i + 1, name, price, stock);
    }
    fclose(file);
}

void addRestockRecord(const char *itemName, int quantity) {
    if (restockCount >= MAX_RESTOCK_RECORDS) {
        printf("補貨紀錄已滿，無法新增。\n");
        //清空紀錄使用
        printf("為您清空過往紀錄");
        FILE *file = fopen(RESTOCK_FILE, "w"); // 使用 "w" 清空
        if (!file) {
            printf("無法打開補貨紀錄檔案。\n");
            return;
        }
        fprintf(file, "%s %d\n", itemName, quantity);
        fclose(file);
        return;
    }

    strcpy(restockRecords[restockCount].itemName, itemName);
    restockRecords[restockCount].quantity = quantity;
    restockCount++;

    // 同步保存補貨紀錄到文件
    FILE *file = fopen(RESTOCK_FILE, "a"); // 使用 "a" 追加模式
    if (!file) {
        printf("無法打開補貨紀錄檔案。\n");
        return;
    }
    fprintf(file, "%s %d\n", itemName, quantity);
    fclose(file);
}


//查看補貨紀錄
void viewRestockRecords(void) {
    printf("\n補貨紀錄內容：\n");

    FILE *file = fopen(RESTOCK_FILE, "r");
    if (!file) {
        printf("尚無補貨紀錄。\n");
        return;
    }

    char itemName[20];
    int quantity;
    while (fscanf(file, "%s %d", itemName, &quantity) == 2) {
        printf("商品: %s, 補貨數量: %d\n", itemName, quantity);
    }
    fclose(file);
}

User *findOrAddUser(const char *name){
    // 查找使用者
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return &users[i];
        }
    }

    // 如果未找到，新增使用者
    users = realloc(users, (userCount + 1) * sizeof(User));
    if (users == NULL) {
        printf("記憶體分配失敗！\n");
        exit(EXIT_FAILURE);
    }

    strcpy(users[userCount].name, name);
    memset(users[userCount].history, 0, sizeof(users[userCount].history));
    userCount++;
    return &users[userCount - 1];
}

// 讀取庫存
void loadInventory() {
    FILE *file = fopen(INVENTORY_FILE, "r");
    if (!file) {
        //printf("無法打開 %s，使用預設庫存。\n", INVENTORY_FILE);
        // 初始化預設庫存
        strcpy(items[0].name, "麥香紅茶"); items[0].price = 40; items[0].stock = 10;
        strcpy(items[1].name, "寶礦力水得"); items[1].price = 40; items[1].stock = 8;
        strcpy(items[2].name, "可樂"); items[2].price = 25; items[1].stock = 6;
        strcpy(items[3].name, "麥香奶茶"); items[0].price = 35; items[0].stock = 10;
        strcpy(items[4].name, "三合一咖啡"); items[1].price = 40; items[1].stock = 7;
        strcpy(items[5].name, "雪碧"); items[2].price = 25; items[1].stock = 4;
        strcpy(items[6].name, "麥香綠茶"); items[0].price = 50; items[0].stock = 3;
        strcpy(items[7].name, "無糖黑咖啡"); items[1].price = 25; items[1].stock = 2;
        strcpy(items[8].name, "舒跑"); items[2].price = 20; items[1].stock = 6;
        strcpy(items[9].name, "純喫綠茶"); items[0].price = 15; items[0].stock = 8;
        strcpy(items[10].name, "保利達蠻牛"); items[1].price = 25; items[1].stock = 5;
        strcpy(items[11].name, "麥茶"); items[2].price = 30; items[1].stock = 7;

        return;
    }

    for (int i = 0; i < ITEM_COUNT; i++) {
        fscanf(file, "%s %d %d", items[i].name, &items[i].price, &items[i].stock);
    }
    fclose(file);
}

// 保存庫存
void saveInventory() {
    FILE *file = fopen(INVENTORY_FILE, "w");
    if (!file) {
        printf("無法打開 %s 保存庫存！\n", INVENTORY_FILE);
        return;
    }

    for (int i = 0; i < ITEM_COUNT; i++) {
        fprintf(file, "%s %d %d\n", items[i].name, items[i].price, items[i].stock);
    }
    fclose(file);
}

// 讀取補貨記錄
void loadRestockRecords() {
    FILE *file = fopen(RESTOCK_FILE, "r");
    if (!file) {
        //printf("無法打開 %s，補貨紀錄為空。\n", RESTOCK_FILE);
        return;
    }

    while (fscanf(file, "%s %d", restockRecords[restockCount].itemName, &restockRecords[restockCount].quantity) == 2) {
        restockCount++;
    }
    fclose(file);
}


//保存補貨紀錄至 restock_records.txt
void saveRestockRecords(void) {
    FILE *file = fopen(RESTOCK_FILE, "w");
    if (!file) {
        printf("尚無補貨紀錄。\n");
        return;
    }
    for (int i = 0; i < restockCount; i++) {
        fprintf(file, "%s %d\n", restockRecords[i].itemName, restockRecords[i].quantity);
    }
    fclose(file);
}

//保存購買紀錄至 purchase_records.txt
void savePurchaseRecord(const char *userName, const char *itemName, int quantity) {
    FILE *file = fopen(PURCHASE_FILE, "a");
    if (!file) {
        printf("無法打開購買紀錄檔案！\n");
        return;
    }

    fprintf(file, "%s %s %d\n", userName, itemName, quantity);
    fclose(file);
}


void viewPurchaseRecordsByUser(const char *account) {
    FILE *file = fopen(PURCHASE_FILE, "r");
    if (!file) {
        printf("尚無購買紀錄\n");
        return;
    }

    char userName[20], itemName[20];
    int quantity;
    int found = 0;

    printf("\n您的購買紀錄 - 帳號: %s\n", account);
    while (fscanf(file, "%s %s %d", userName, itemName, &quantity) == 3) {
        if (strcmp(userName, account) == 0) {
            printf("商品: %s, 數量: %d\n", itemName, quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("您沒有任何購買紀錄。\n");
    }

    fclose(file);
}

// 移除字串末尾的換行符
void trimNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void viewPurchaseRecordsByAdmin(void) {
    char account[20];
    int choice;

    do {
        printf("\n請輸入要查詢的購買者帳號: ");
        fflush(stdout);
        scanf("%s", account);

        FILE *file = fopen(PURCHASE_FILE, "r");
        if (!file) {
            printf("尚無購買紀錄。\n");
            return;
        }

        char line[100];
        int found = 0;

        printf("購買紀錄 - 帳號: %s\n", account);
        while (fgets(line, sizeof(line), file)) {
            char temp[100];
            char *token;

            strcpy(temp, line);
            trimNewline(temp); // 移除末尾的換行符

            token = strtok(temp, " "); // 使用空白分割字串，取得帳號


            if (token != NULL && strcmp(token, account) == 0) {
                printf("%s", line); // 輸出找到的該行
                found = 1;  // 標記為已找到
            }


        }

        fclose(file);

        if (!found) {
            printf("未找到該購買者紀錄。\n");
            while (1) {
                printf("1=重新輸入, 0=退出此功能: ");
                if (scanf("%d", &choice) != 1) {
                    // 如果用戶輸入非整數，清除輸入緩衝區
                    while(getchar()!= '\n');
                    printf("無效選項，請重新輸入。\n");
                } else if (choice == 0 || choice == 1) {
                    break; // 正確選項，跳出循環
                }else {
                    printf("無效選項，請重新輸入。\n");
                }
            }
        } else {
            printf("查詢完成。\n");
            break;
        }
    } while (choice != 0);
}

//查看所有購買紀錄
void viewAllPurchaseRecordsByAdmin(void) {
    int choice;

        FILE *file = fopen(PURCHASE_FILE, "r");
        if (!file) {
            printf("尚無購買紀錄。\n");
            return;
        }

        char line[100];

        printf("所有購買紀錄:\n");
        while (fgets(line, sizeof(line), file)) {
            char temp[100];
            char *token;

            strcpy(temp, line);
            trimNewline(temp); // 移除末尾的換行符
            printf("%s", line); // 輸出找到的該行

        }

        fclose(file);
        printf("查詢完成。\n");

}


