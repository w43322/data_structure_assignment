#include"avltree.h"

int calheight(struct AVLNode *p)
{
    //qDebug()<<"calheight"<<endl<<"    "<<"val"<<p->data<<"addr"<<p;
    if(p==NULL)return 0;
    if(p->left&&p->right)
    {
        if(p->left->height<p->right->height)
            return p->right->height+1;
        else
            return p->left->height+1;
    }
    else if(p->left&&p->right==NULL)
        return p->left->height+1;
    else if(p->left==NULL&&p->right)
        return p->right->height+1;
    return 1;
}

int bf(struct AVLNode *n)
{
    if(n==NULL)return 0;

    if(n->left&&n->right)
        return n->left->height-n->right->height;
    else if(n->left&&n->right==NULL)
        return n->left->height;
    else if(n->left==NULL&&n->right)
        return -n->right->height;
    return 0;//not used
}

struct AVLNode *llrotation(struct AVLNode *n)
{
    struct AVLNode *p;
    struct AVLNode *tp;
    p=n;
    tp=p->left;

    p->left=tp->right;
    tp->right=p;

    p->height=calheight(p);
    tp->height=calheight(tp);

    return tp;
}


struct AVLNode *rrrotation(struct AVLNode *n)
{
    struct AVLNode *p;
    struct AVLNode *tp;
    p=n;
    tp=p->right;

    p->right=tp->left;
    tp->left=p;

    p->height=calheight(p);
    tp->height=calheight(tp);

    return tp;
}


struct AVLNode *rlrotation(struct AVLNode *n)
{
    struct AVLNode *p;
    struct AVLNode *tp;
    struct AVLNode *tp2;
    p=n;
    tp=p->right;
    tp2=p->right->left;

    p->right=tp2->left;
    tp->left=tp2->right;
    tp2->left=p;
    tp2->right=tp;

    p->height=calheight(p);
    tp->height=calheight(tp);
    tp2->height=calheight(tp2);

    return tp2;
}

struct AVLNode *lrrotation(struct AVLNode *n)
{
    struct AVLNode *p;
    struct AVLNode *tp;
    struct AVLNode *tp2;
    p=n;
    tp=p->left;
    tp2=p->left->right;

    p->left=tp2->right;
    tp->right=tp2->left;
    tp2->right=p;
    tp2->left=tp;

    p->height=calheight(p);
    tp->height=calheight(tp);
    tp2->height=calheight(tp2);

    return tp2;
}

struct AVLNode *insert(struct AVLNode *r,int data)
{
    qDebug()<<"insert addr"<<r;
    if(r==NULL)//??????????????????????????????????????????????????????
    {
        struct AVLNode *n;
        n=new struct AVLNode;
        n->data=data;
        //n->lab.setText(QString::number(data));
        r=n;
        r->left=r->right=NULL;
        r->height=1;
        //qDebug()<<"newly created addr"<<r;
        return r;
    }
    else
    {
        if(data<r->data)
            r->left=insert(r->left,data);
        else if(data>r->data)
            r->right=insert(r->right,data);
    }

    r->height=calheight(r);//??????????????????????????????????????????????????????????????????????????????

    //qDebug()<<"before raotation node"<<r->data<<"bf"<<bf(r);

    //??????????????????????????????
    if(bf(r)>1&&bf(r->left)>0)
        r=llrotation(r);
    else if(bf(r)>1&&bf(r->left)<=0)
        r=lrrotation(r);
    else if(bf(r)<-1&&bf(r->right)<=0)
        r=rrrotation(r);
    else if(bf(r)<-1&&bf(r->right)>0)
        r=rlrotation(r);

    //qDebug()<<"after rotation node"<<r->data<<"bf"<<bf(r);
    //r->height=calheight(r);


    return r;

}

struct AVLNode *FIND(struct AVLNode *r,int data)
{
    if(r==NULL)return NULL;
    if(data<r->data)
        return FIND(r->left,data);
    else if(data>r->data)
        return FIND(r->right,data);
    else return r;
}

struct AVLNode *deleteAVLNode(struct AVLNode *p,int data,struct AVLNode *root)
{

    if(p->left==NULL&&p->right==NULL)//????????????????????????????????????????????????
    {
        if(p==root)//?????????AVL?????????
            root=NULL;
        delete p;
        return NULL;
    }

    struct AVLNode *q;
    //??????????????????????????????????????????????????????
    if(p->data<data)
        p->right=deleteAVLNode(p->right,data,root);
    else if(p->data>data)
        p->left=deleteAVLNode(p->left,data,root);
    else//???????????????????????????
    {
        if(p->left!=NULL)//??????????????????????????????????????????????????????????????????????????????
        {
            q=inpre(p->left);
            p->data=q->data;
            //p->lab.setText(QString::number(p->data));
            p->left=deleteAVLNode(p->left,q->data,root);
        }
        else//????????????????????????????????????????????????????????????????????????
        {
            q=insuc(p->right);
            p->data=q->data;
            //p->lab.setText(QString::number(p->data));
            p->right=deleteAVLNode(p->right,q->data,root);
        }
    }

    p->height=calheight(p);

    qDebug()<<"before raotation node"<<p->data<<"height"<<p->height<<"bf"<<bf(p);

    if(bf(p)>1&&bf(p->left)>0)
        p=llrotation(p);
    else if(bf(p)>1&&bf(p->left)<=0)
        p=lrrotation(p);
    else if(bf(p)<-1&&bf(p->right)<=0)
        p=rrrotation(p);
    else if(bf(p)<-1&&bf(p->right)>0)
        p=rlrotation(p);

    qDebug()<<"after rotation node"<<p->data<<"height"<<p->height<<"bf"<<bf(p);

    return p;
}

struct AVLNode *inpre(struct AVLNode* p)
{
    while(p->right!=NULL)
        p=p->right;
    return p;
}

struct AVLNode *insuc(struct AVLNode* p)
{
    while(p->left!=NULL)
        p=p->left;
    return p;
}
