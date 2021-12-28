/*
ListNode* insert_last(ListNode* head, element data)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;

    if (head == NULL) {
        head = node;
        node->link = head;
    }
    else {
        node->link = head->link;// (1)
        head->link = node;// (2)
        head = node;
    }

    return head;// 변경된 헤드 포인터를 반환한다.
}
*/