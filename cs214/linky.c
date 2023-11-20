struct list {
    int data;
    struct list *next;
};

// using a pointer avoids a recursive definition
//allows us to use NULL to indicate "no more nodes"

//NULL is a special pointer that never points to anything

//we need a way to create an object that is not associated with a variable

    //malloc() is used for "dynamic allocation"
        //dynamic meaning the compiler doesn't need to know how much space we need

        struct node *head = malloc(sizeof(struct node));
        head.data = 0;
        head.next = NULL;

    //we can now create and use linked lists

        for (p = head; p != NULL; p = (*p).next){
            //do stuff
        }