#include"main.h"
void ClearWindow()
{
    #if defined(__APPLE__)||defined(__linux__)
        system("clear");
    #else
        system("cls");
    #endif
}
void ShowWindow()
{
    ClearWindow();
    //printf("--------10--------20--------30--------40\n");
    printf("________________________________________\n");
    printf("|                                      |\n");
    printf("| 0-exit                               |\n");
    printf("| 1-add                                |\n");
    printf("| 2-find                               |\n");
    printf("|______________________________________|\n");
}
int main()
{
    int cmd;
    char buf[max_string_length];
    TreeNode *root=(TreeNode*)malloc(sizeof(TreeNode));
    root->data[0]='/';
    root->data[1]='\0';
    root->firstchild=NULL;
    root->nextsibling=NULL;
    root->terminate=0;

    ShowWindow();
    while(scanf("%d",&cmd),cmd)
    {
        ClearWindow();
        switch(cmd)
        {
            case 1:
            printf("please input URL:\n");
            scanf("%s",buf);
            Add(root,buf);
            break;
            case 2:
            printf("please input URL:\n");
            scanf("%s",buf);
            TreeNode *res=Find(root,buf);
            if(res)
            {
                if(res->terminate)
                    printf("FULL MATCH ");
                printf("FOUND\n");
            }
            else
                printf("NOTFOUND\n");
            break;
            default:
            break;
        }
        printf("\npress any key to continue...");
        getchar();getchar();
        ShowWindow();
    }
}

/*
cd "/Users/w43322/Desktop/code/data_structure_assignment/实验/3/" && gcc main.c tree.c -o main
"/Users/w43322/Desktop/code/data_structure_assignment/实验/3/"main
*/

/*
【问题描述】
互联网域名系统是一个典型的树形层次结构。从根节点往下的第一层是顶层域，如cn、com等，最底层（第四层）是叶子结点，如www等。因此，域名搜索可以看成是树的遍历问题。
【实验要求】
设计搜索互联网域名的程序。
（1）采用树的孩子兄弟链表等存储结构。
（2）创建树形结构。
（3）通过深度优先遍历搜索。
（4）通过层次优先遍历搜索。
*/
