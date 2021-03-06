#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



#include "stest.h"
#include "dqueue.h"





struct tmp_data
{
   dqueue_node node;
   int         data;
};



#define DECLARE_TMP_DATA(name) \
    struct tmp_data name = { {NULL, NULL}, 0}





TEST(test_dqueue_empty)
{
    DECLARE_DQUEUE(dqueue);
    DECLARE_TMP_DATA(d1);


    TEST_ASSERT(dqueue_empty(&dqueue));     //dqueue must be empty

    dqueue_push_front(&d1.node, &dqueue);   //now d1 is first

    TEST_ASSERT(!dqueue_empty(&dqueue));    //now dqueue is NOT empty


    TEST_PASS(NULL);
}



TEST(test_dqueue_is_first)
{
    DECLARE_DQUEUE(dqueue1);
    DECLARE_DQUEUE(dqueue2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    dqueue_push_front(&d1.node, &dqueue1);              //now d1 is first

    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue1));   //d1 must be first


    dqueue_push_front(&d2.node, &dqueue1);              //now d2 is first

    TEST_ASSERT(dqueue_is_first(&d2.node, &dqueue1));   //d2 must be first
    TEST_ASSERT(!dqueue_is_first(&d1.node, &dqueue1));  //d1 is not first (d1 is last)


    dqueue_push_front(&d3.node, &dqueue2);              //now d3 is first
    TEST_ASSERT(!dqueue_is_first(&d3.node, &dqueue1));  //d3 is not first (d3 out of the dqueue1.)
    TEST_ASSERT(dqueue_is_first(&d3.node, &dqueue2));   //d3 is first in dqueue2


    TEST_PASS(NULL);
}



TEST(test_dqueue_is_last)
{
    DECLARE_DQUEUE(dqueue1);
    DECLARE_DQUEUE(dqueue2);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    dqueue_push_front(&d1.node, &dqueue1);              //now d1 is first

    TEST_ASSERT(dqueue_is_last(&d1.node, &dqueue1));    //d1 must be first and last (list is circular)


    dqueue_push_back(&d2.node, &dqueue1);               //now d2 is last

    TEST_ASSERT(dqueue_is_last(&d2.node, &dqueue1));    //d2 must be last
    TEST_ASSERT(!dqueue_is_last(&d1.node, &dqueue1));   //now d1 dont must be last (d1 is first)


    dqueue_push_front(&d3.node, &dqueue2);             //now d3 is first

    TEST_ASSERT(!dqueue_is_last(&d3.node, &dqueue1));  //d3 is not first (d3 out of the dqueue1)
    TEST_ASSERT(dqueue_is_last(&d3.node, &dqueue2));   //d3 is first and last in dqueue2


    TEST_PASS(NULL);
}



TEST(test_dqueue_is_singular)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    TEST_ASSERT(!dqueue_is_singular(&dqueue));     //list must be empty (not singular)


    dqueue_push_front(&d1.node, &dqueue);          //now d1 is first

    TEST_ASSERT(dqueue_is_singular(&dqueue));      //list must be singular (in list only d1)


    dqueue_push_back(&d2.node, &dqueue);           //now d2 is last

    TEST_ASSERT(!dqueue_is_singular(&dqueue));     //list dont must be singular (in list d1,d2)


    TEST_PASS(NULL);
}



TEST(test_dqueue_size)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    TEST_ASSERT(dqueue_size(&dqueue) == 0);    //size == 0 (dqueue is empty)

    dqueue_push_front(&d1.node, &dqueue);      //now d1 is first
    TEST_ASSERT(dqueue_size(&dqueue) == 1);    //size == 1 (d1)
    TEST_ASSERT(!dqueue_empty(&dqueue));       //dqueue dont must be empty

    dqueue_push_back(&d2.node, &dqueue);     //now d2 is last
    TEST_ASSERT(dqueue_size(&dqueue) == 2);  //size == 2 (d1,d2)
    TEST_ASSERT(!dqueue_empty(&dqueue));     //dqueue dont must be empty

    dqueue_push_back(&d3.node, &dqueue);     //now d3 is last
    TEST_ASSERT(dqueue_size(&dqueue) == 3);  //size == 3 (d1,d2, d3)
    TEST_ASSERT(!dqueue_empty(&dqueue));     //dqueue dont must be empty


    //delete
    dqueue_del(&d1.node, &dqueue);           //now d1 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 2);  //size == 2 (d2,d3)
    TEST_ASSERT(!dqueue_empty(&dqueue));     //dqueue dont must be empty

    dqueue_del(&d2.node, &dqueue);           //now d2 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 1);  //size == 1 (d3)
    TEST_ASSERT(!dqueue_empty(&dqueue));     //dqueue dont must be empty

    dqueue_del(&d3.node, &dqueue);           //now d3 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 0);  //size == 0 (list is empty)
    TEST_ASSERT(dqueue_empty(&dqueue));      //dqueue must be empty

    TEST_PASS(NULL);
}



TEST(test_dqueue_del)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    TEST_ASSERT(dqueue_size(&dqueue) == 0);  //size == 0 (list is empty)

    dqueue_push_front(&d1.node, &dqueue);    //now d1 is first
    dqueue_push_back(&d2.node, &dqueue);     //now d2 is last
    dqueue_push_back(&d3.node, &dqueue);     //now d3 is last
    TEST_ASSERT(dqueue_size(&dqueue) == 3);  //size == 3 (d1,d2, d3)


    //delete
    TEST_ASSERT(!dqueue_empty(&dqueue));     //d1 in list
    dqueue_del(&d1.node, &dqueue);           //now d1 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 2);  //size == 2 (d2,d3)
    TEST_ASSERT(dlist_empty(&d1.node));      //d1 is not in list


    TEST_ASSERT(!dqueue_empty(&dqueue));      //d2 in list
    dqueue_del(&d2.node, &dqueue);            //now d2 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 1);   //size == 1 (d3)
    TEST_ASSERT(dlist_empty(&d2.node));       //d2 is not in list

    TEST_ASSERT(!dqueue_empty(&dqueue));      //d3 in list
    dqueue_del(&d3.node, &dqueue);            //now d3 is not in list
    TEST_ASSERT(dqueue_size(&dqueue) == 0);   //size == 0 (list is empty)
    TEST_ASSERT(dqueue_empty(&dqueue));
    TEST_ASSERT(dlist_empty(&d3.node));       //d3 is not in list

    TEST_PASS(NULL);
}



TEST(test_dqueue_pop_front)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    dqueue_push_front(&d1.node, &dqueue);    //now d1 is first
    dqueue_push_front(&d2.node, &dqueue);    //now d2 is first
    dqueue_push_front(&d3.node, &dqueue);    //now d3 is first
    TEST_ASSERT(dqueue_size(&dqueue) == 3);  //size == 3 (d3, d2, d1)


    dqueue_pop_front(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 2);           //size == 2 (d2, d1)
    TEST_ASSERT(dlist_empty(&d3.node));
    TEST_ASSERT(dqueue_is_first(&d2.node, &dqueue));  //(d2, d1)


    dqueue_pop_front(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 1);          //size == 1 (d1)
    TEST_ASSERT(dlist_empty(&d2.node));
    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue)); //(d1)


    dqueue_pop_front(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 0);           //size == 0 ()
    TEST_ASSERT(dqueue_empty(&dqueue));
    TEST_ASSERT(dlist_empty(&d1.node));


    //dqueue empty
    dqueue_pop_front(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 0);           //size == 0 ()
    TEST_ASSERT(dqueue_empty(&dqueue));


    TEST_PASS(NULL);
}



TEST(test_dqueue_pop_back)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);


    //add
    dqueue_push_front(&d1.node, &dqueue);   //now d1 is first
    dqueue_push_front(&d2.node, &dqueue);   //now d2 is first
    dqueue_push_front(&d3.node, &dqueue);   //now d3 is first
    TEST_ASSERT(dqueue_size(&dqueue) == 3); //size == 3 (d3, d2, d1)


    dqueue_pop_back(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 2);           //size == 2 (d2, d1)
    TEST_ASSERT(dlist_empty(&d1.node));
    TEST_ASSERT(dqueue_is_first(&d3.node, &dqueue));  //(d3, d2)


    dqueue_pop_back(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 1);          //size == 1 (d3)
    TEST_ASSERT(dlist_empty(&d2.node));
    TEST_ASSERT(dqueue_is_first(&d3.node, &dqueue)); //(d3)


    dqueue_pop_back(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 0);           //size == 0 ()
    TEST_ASSERT(dqueue_empty(&dqueue));
    TEST_ASSERT(dlist_empty(&d3.node));


    //list empty
    dqueue_pop_back(&dqueue);
    TEST_ASSERT(dqueue_size(&dqueue) == 0);           //size == 0 ()
    TEST_ASSERT(dqueue_empty(&dqueue));


    TEST_PASS(NULL);
}



TEST(test_dqueue_replace_init)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    //add
    dqueue_push_front(&d1.node, &dqueue);

    TEST_ASSERT(dqueue_is_last(&d1.node, &dqueue));    //d1 in list
    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue));   //d1 in list
    TEST_ASSERT(!dqueue_is_last(&d2.node, &dqueue));   //d2 dont in list


    dqueue_replace_init(&d1.node, &d2.node);


    TEST_ASSERT(dlist_empty(&d1.node));               //d1 must be clean

    TEST_ASSERT(dqueue_size(&dqueue) == 1);           //size == 1 (d1)
    TEST_ASSERT(!dqueue_is_last(&d1.node, &dqueue));  //d1 dont in list
    TEST_ASSERT(dqueue_is_last(&d2.node, &dqueue));


    TEST_PASS(NULL);
}



TEST(test_dqueue_move_to_front)
{
    DECLARE_DQUEUE(dqueue1);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    //add
    dqueue_push_front(&d1.node, &dqueue1);
    dqueue_push_front(&d2.node, &dqueue1);


    dqueue_move_to_front(&d1.node, &dqueue1);


    TEST_ASSERT(dqueue_size(&dqueue1) == 2);
    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue1));
    TEST_ASSERT(!dqueue_is_first(&d2.node, &dqueue1));   //d2 is not first
    TEST_ASSERT(dqueue_is_last(&d2.node, &dqueue1));


    TEST_PASS(NULL);
}



TEST(test_dqueue_move_to_back)
{
    DECLARE_DQUEUE(dqueue1);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    //add
    dqueue_push_front(&d1.node, &dqueue1);
    dqueue_push_front(&d2.node, &dqueue1);


    dqueue_move_to_back(&d1.node, &dqueue1);


    TEST_ASSERT(dqueue_size(&dqueue1) == 2);
    TEST_ASSERT(dqueue_is_last(&d1.node, &dqueue1));
    TEST_ASSERT(dqueue_is_first(&d2.node, &dqueue1));


    TEST_PASS(NULL);
}



TEST(test_dqueue_rotate_left)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);
    DECLARE_TMP_DATA(d4);


    //add
    dqueue_push_front(&d4.node, &dqueue);
    dqueue_push_front(&d3.node, &dqueue);
    dqueue_push_front(&d2.node, &dqueue);
    dqueue_push_front(&d1.node, &dqueue);               //[head] <-> [d1] <-> [d2] <-> [d3] <-> [d4]



    dqueue_rotate_left(&dqueue);                        //[d1] <-> [head] <-> [d2] <-> [d3] <-> [d4]

    TEST_ASSERT(dqueue_is_last(&d1.node, &dqueue));     //d1 last
    TEST_ASSERT(dqueue_is_first(&d2.node, &dqueue));    //d2 first


    dqueue_rotate_left(&dqueue);                        //[d1] <-> [d2] <-> [head] <-> [d3] <-> [d4]

    TEST_ASSERT(dqueue_is_last(&d2.node, &dqueue));     //d2 last
    TEST_ASSERT(dqueue_is_first(&d3.node, &dqueue));    //d3 first


    dqueue_rotate_left(&dqueue);                        //[d1] <-> [d2] <-> [d3] <-> [head] <-> [d4]

    TEST_ASSERT(dqueue_is_last(&d3.node, &dqueue));     //d3 last
    TEST_ASSERT(dqueue_is_first(&d4.node, &dqueue));    //d4 first


    dqueue_rotate_left(&dqueue);                        //[d2] <-> [d3] <-> [d4] <-> [head] <-> [d1]

    TEST_ASSERT(dqueue_is_last(&d4.node, &dqueue));     //d4 last
    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue));    //d1 first


    TEST_PASS(NULL);
}



TEST(test_dqueue_rotate_right)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);
    DECLARE_TMP_DATA(d3);
    DECLARE_TMP_DATA(d4);


    //add
    dqueue_push_front(&d4.node, &dqueue);
    dqueue_push_front(&d3.node, &dqueue);
    dqueue_push_front(&d2.node, &dqueue);
    dqueue_push_front(&d1.node, &dqueue);              //[head] <-> [d1] <-> [d2] <-> [d3] <-> [d4]



    dqueue_rotate_right(&dqueue);                       //[d3] <-> [head] <-> [d4] <-> [d1] <-> [d2]

    TEST_ASSERT(dqueue_is_last(&d3.node, &dqueue));     //d3 last
    TEST_ASSERT(dqueue_is_first(&d4.node, &dqueue));    //d4 first


    dqueue_rotate_right(&dqueue);                       //[d1] <-> [d2] <-> [head] <-> [d3] <-> [d4]

    TEST_ASSERT(dqueue_is_last(&d2.node, &dqueue));     //d2 last
    TEST_ASSERT(dqueue_is_first(&d3.node, &dqueue));    //d3 first


    dqueue_rotate_right(&dqueue);                       //[d3] <-> [d4] <-> [d1] <-> [head] <-> [d2]

    TEST_ASSERT(dqueue_is_last(&d1.node, &dqueue));     //d1 last
    TEST_ASSERT(dqueue_is_first(&d2.node, &dqueue));    //d2 first


    dqueue_rotate_right(&dqueue);                       //[d2] <-> [d3] <-> [d4] <-> [head] <-> [d1]

    TEST_ASSERT(dqueue_is_last(&d4.node, &dqueue));     //d4 last
    TEST_ASSERT(dqueue_is_first(&d1.node, &dqueue));    //d1 first


    TEST_PASS(NULL);
}



TEST(test_dqueue_splice_front)
{
    DECLARE_DQUEUE(dqueue1);
    DECLARE_DQUEUE(dqueue2);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue1);
    }

    dqueue_splice_front(&dqueue1, &dqueue2);


    TEST_ASSERT( dqueue_size(&dqueue1) == 0 );
    TEST_ASSERT( dqueue_size(&dqueue2) == COUNT_NODES );


    i=0;
    dqueue_data_citer(it, &dqueue2, struct tmp_data, node)
    {
        TEST_ASSERT(it->data == i);
        i++;
    }

    //is front
    TEST_ASSERT( dqueue2.head.next == &nodes[0].node );


    TEST_PASS(NULL);
}



TEST(test_dqueue_splice_back)
{
    DECLARE_DQUEUE(dqueue1);
    DECLARE_DQUEUE(dqueue2);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue1);
    }

    dqueue_splice_back(&dqueue1, &dqueue2);


    TEST_ASSERT( dqueue_size(&dqueue1) == 0 );
    TEST_ASSERT( dqueue_size(&dqueue2) == COUNT_NODES );


    i=0;
    dqueue_data_citer(it, &dqueue2, struct tmp_data, node)
    {
        TEST_ASSERT(it->data == i);
        i++;
    }

    //is back
    TEST_ASSERT( dqueue2.head.next == &nodes[0].node );


    TEST_PASS(NULL);
}



TEST(test_dqueue_reverse)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    dqueue_node *it;


    for(i=0; i < COUNT_NODES; i++)
    {
        dqueue_push_back(&nodes[i].node, &dqueue);
    }

    TEST_ASSERT( dqueue_size(&dqueue) == COUNT_NODES );

    i=0;
    dqueue_citer(it, &dqueue)
    {
        TEST_ASSERT( it == &nodes[i].node );  //test nodes
        i++;
    }

    dqueue_reverse(&dqueue);
    TEST_ASSERT( dqueue_size(&dqueue) == COUNT_NODES );

    i=COUNT_NODES-1;
    dqueue_citer(it, &dqueue)
    {
        TEST_ASSERT( it == &nodes[i].node );  //test nodes
        i--;
    }


    TEST_PASS(NULL);
}



TEST(test_dqueue_swap)
{
    DECLARE_DQUEUE(dqueue1);
    DECLARE_DQUEUE(dqueue2);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    dqueue_node *it;


    for(i=0; i < COUNT_NODES; i++)
    {
        dqueue_push_back(&nodes[i].node, &dqueue1);
    }

    TEST_ASSERT( dqueue_size(&dqueue1) == COUNT_NODES );
    TEST_ASSERT( dqueue_size(&dqueue2) == 0 );

    i=0;
    dqueue_citer(it, &dqueue1)
    {
        TEST_ASSERT( it == &nodes[i].node );  //test nodes
        i++;
    }


    //swap self
    dqueue_swap(&dqueue1, &dqueue1);
    TEST_ASSERT( dqueue_size(&dqueue1) == COUNT_NODES );

    i=0;
    dqueue_citer(it, &dqueue1)
    {
        TEST_ASSERT( it == &nodes[i].node );  //test nodes
        i++;
    }



    dqueue_swap(&dqueue1, &dqueue2);
    TEST_ASSERT( dqueue_size(&dqueue1) == 0 );
    TEST_ASSERT( dqueue_size(&dqueue2) == COUNT_NODES );


    i=0;
    dqueue_citer(it, &dqueue2)
    {
        TEST_ASSERT( it == &nodes[i].node );  //test nodes
        i++;
    }


    dqueue_swap(&dqueue1, &dqueue1);
    TEST_ASSERT( dqueue_size(&dqueue1) == 0 );


    TEST_PASS(NULL);
}



//---------------- Get Data from node ----------------



TEST(test_dqueue_data)
{
    DECLARE_TMP_DATA(d1);

    TEST_ASSERT( dqueue_data(&d1.node, struct tmp_data, node) == &d1 );

    TEST_PASS(NULL);
}



TEST(test_dqueue_data_or_null)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);

    dqueue_init_node(&d1.node);

    TEST_ASSERT( dqueue_data_or_null(&d1.node, struct tmp_data, node) == NULL );


    dqueue_push_front(&d1.node, &dqueue);

    TEST_ASSERT( dqueue_data_or_null(&d1.node, struct tmp_data, node) == &d1 );


    TEST_PASS(NULL);
}



TEST(test_dqueue_first_data)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    dqueue_push_front(&d1.node, &dqueue);

    TEST_ASSERT( dqueue_first_data(&dqueue, struct tmp_data, node) == &d1 );


    dqueue_push_front(&d2.node, &dqueue);

    TEST_ASSERT( dqueue_first_data(&dqueue, struct tmp_data, node) == &d2 );
    TEST_ASSERT( dqueue_first_data(&dqueue, struct tmp_data, node) != &d1 ); //now d2 first


    TEST_PASS(NULL);
}



TEST(test_dqueue_last_data)
{
    DECLARE_DQUEUE(dqueue);

    DECLARE_TMP_DATA(d1);
    DECLARE_TMP_DATA(d2);


    dqueue_push_back(&d1.node, &dqueue);

    TEST_ASSERT( dqueue_last_data(&dqueue, struct tmp_data, node) == &d1 );


    dqueue_push_back(&d2.node, &dqueue);

    TEST_ASSERT( dqueue_last_data(&dqueue, struct tmp_data, node) == &d2 );
    TEST_ASSERT( dqueue_last_data(&dqueue, struct tmp_data, node) != &d1 ); //now d2 last


    TEST_PASS(NULL);
}



//---------------- Iterator ----------------



TEST(test_dqueue_citer)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    dqueue_node *it;


    for(i=0; i < COUNT_NODES; i++)
        dqueue_push_back(&nodes[i].node, &dqueue);


    i=0;
    dqueue_citer(it, &dqueue)
    {
        TEST_ASSERT( it == &nodes[i].node );  //test nodes
        i++;
    }


    TEST_PASS(NULL);
}



TEST(test_dqueue_criter)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    dqueue_node *it;


    for(i=0; i < COUNT_NODES; i++)
        dqueue_push_front(&nodes[i].node, &dqueue);


    i=0;
    dqueue_criter(it, &dqueue)
    {
        TEST_ASSERT( it == &nodes[i].node );  //test nodes
        i++;
    }


    TEST_PASS(NULL);
}



TEST(test_dqueue_iter)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    dqueue_node *it;
    dqueue_node *tmp_it;


    for(i=0; i < COUNT_NODES; i++)
        dqueue_push_back(&nodes[i].node, &dqueue);


    TEST_ASSERT( dqueue_size(&dqueue) == COUNT_NODES );


    i=0;
    dqueue_iter(it, tmp_it, &dqueue)   //dont change
    {
        TEST_ASSERT( it == &nodes[i].node );     //test nodes
        i++;
    }


    i=0;
    dqueue_iter(it, tmp_it, &dqueue)   //+ change (del)
    {
        if(i & 1)
            dqueue_del(it, &dqueue);
        i++;
    }


    TEST_ASSERT( dqueue_size(&dqueue) == (COUNT_NODES/2) );


    TEST_PASS(NULL);
}



TEST(test_dqueue_riter)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    dqueue_node *it;
    dqueue_node *tmp_it;


    for(i=0; i < COUNT_NODES; i++)
        dqueue_push_front(&nodes[i].node, &dqueue);


    TEST_ASSERT( dqueue_size(&dqueue) == COUNT_NODES );


    i=0;
    dqueue_riter(it, tmp_it, &dqueue)   //dont change
    {
        TEST_ASSERT( it == &nodes[i].node );      //test nodes
        i++;
    }


    i=0;
    dqueue_riter(it, tmp_it, &dqueue)   //+ change (del)
    {
        if(i & 1)
            dqueue_del(it, &dqueue);
        i++;
    }

    TEST_ASSERT( dqueue_size(&dqueue) == (COUNT_NODES/2) );


    TEST_PASS(NULL);
}



TEST(test_dqueue_data_citer)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    struct tmp_data *it;



    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }



    i=0;
    dqueue_data_citer(it, &dqueue, struct tmp_data, node)
    {
        TEST_ASSERT( it->data == nodes[i].data );     //test nodes
        i++;
    }


    TEST_PASS(NULL);
}



TEST(test_dqueue_data_criter)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data nodes[COUNT_NODES];
    struct tmp_data *it;



    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_front(&nodes[i].node, &dqueue);
    }


    i=0;
    dqueue_data_criter(it, &dqueue, struct tmp_data, node)
    {
        TEST_ASSERT( it->data == nodes[i].data );     //test nodes
        i++;
    }


    TEST_PASS(NULL);
}



TEST(test_dqueue_data_iter)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;
    dqueue_node      *tmp_it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    i=0;
    dqueue_data_iter(it, &dqueue, tmp_it, struct tmp_data, node)   //+ change (del)
    {
        if(i & 1)
            dqueue_del(&it->node, &dqueue);
        i++;
    }


    TEST_ASSERT( dqueue_size(&dqueue) == (COUNT_NODES/2) );


    i=0;
    dqueue_data_citer(it, &dqueue, struct tmp_data, node)
    {
        TEST_ASSERT(it->data == i);
        i+= 2;
    }


    TEST_PASS(NULL);
}



TEST(test_dqueue_data_riter)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it;
    dqueue_node      *tmp_it;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_front(&nodes[i].node, &dqueue);
    }


    i=0;
    dqueue_data_riter(it, &dqueue, tmp_it, struct tmp_data, node)   //+ change (del)
    {
        if(i & 1)
            dqueue_del(&it->node, &dqueue);
        i++;
    }


    TEST_ASSERT( dqueue_size(&dqueue) == (COUNT_NODES/2) );


    i=0;
    dqueue_data_criter(it, &dqueue, struct tmp_data, node)
    {
        TEST_ASSERT(it->data == i);
        i+= 2;
    }


    TEST_PASS(NULL);
}



//---------------- Algorithm ----------------



void node_inc(dqueue_node *it)
{
    struct tmp_data *data = dqueue_data(it, struct tmp_data, node);

    data->data++;
}



TEST(test_dqueue_for_each)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *it_data;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    dqueue_for_each(dqueue_begin(&dqueue), dqueue_end(&dqueue), node_inc);


    i=0;
    dqueue_data_citer(it_data, &dqueue, struct tmp_data, node)
    {
        TEST_ASSERT( it_data->data == (i+1) );
        i++;
    }


    TEST_PASS(NULL);
}



int comp_less(const dqueue_node *n1,const dqueue_node *n2)
{
    struct tmp_data *d1 = dqueue_data(n1, struct tmp_data, node);
    struct tmp_data *d2 = dqueue_data(n2, struct tmp_data, node);

    return d1->data < d2->data;
}



TEST(test_dqueue_min)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *tmp_data;
    dqueue_node *min;


    min = dqueue_min(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less);
    TEST_ASSERT(min == dqueue_end(&dqueue)); //min == end iterator (list empty)


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    min = dqueue_min(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less);
    tmp_data = dqueue_data(min, struct tmp_data, node);

    TEST_ASSERT(tmp_data->data == 0);


    dqueue_init(&dqueue);  //clear

    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = -i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    min = dqueue_min(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less);
    tmp_data = dqueue_data(min, struct tmp_data, node);

    TEST_ASSERT(tmp_data->data == -(COUNT_NODES-1));


    TEST_PASS(NULL);
}



TEST(test_dqueue_max)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *tmp_data;
    dqueue_node *max;


    max = dqueue_max(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less);
    TEST_ASSERT(max == dqueue_end(&dqueue)); //max == end iterator (list empty)


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    max = dqueue_max(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less);
    tmp_data = dqueue_data(max, struct tmp_data, node);

    TEST_ASSERT(tmp_data->data == COUNT_NODES-1);


    dqueue_init(&dqueue);  //clear

    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = -i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    max = dqueue_max(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less);
    tmp_data = dqueue_data(max, struct tmp_data, node);

    TEST_ASSERT(tmp_data->data == 0);


    TEST_PASS(NULL);
}



TEST(test_dqueue_minmax)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data  nodes[COUNT_NODES];
    struct tmp_data  *tmp_data;
    dqueue_node *res[2];


    dqueue_minmax(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less, res);
    TEST_ASSERT(res[0] == dqueue_end(&dqueue)); //min == end iterator (list empty)
    TEST_ASSERT(res[1] == dqueue_end(&dqueue)); //max == end iterator (list empty)



    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    dqueue_minmax(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less, res);
    tmp_data = dqueue_data(res[0], struct tmp_data, node);
    TEST_ASSERT(tmp_data->data == 0);                       //min

    tmp_data = dqueue_data(res[1], struct tmp_data, node);
    TEST_ASSERT(tmp_data->data == COUNT_NODES-1);           //max


    dqueue_init(&dqueue);  //clear

    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = -i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    dqueue_minmax(dqueue_begin(&dqueue), dqueue_end(&dqueue), comp_less, res);
    tmp_data = dqueue_data(res[0], struct tmp_data, node);
    TEST_ASSERT(tmp_data->data == -(COUNT_NODES-1));        //min

    tmp_data = dqueue_data(res[1], struct tmp_data, node);
    TEST_ASSERT(tmp_data->data == 0);                       //max


    TEST_PASS(NULL);
}



int pred_50(const dqueue_node *it)
{
    struct tmp_data *data = dqueue_data(it, struct tmp_data, node);

    return data->data == 50;
}



TEST(test_dqueue_find)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data   nodes[COUNT_NODES];
    dqueue_node *f;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }


    f = dqueue_find(dqueue_begin(&dqueue), dqueue_end(&dqueue), pred_50);

    TEST_ASSERT( f == &nodes[50].node );


    TEST_PASS(NULL);
}



int pred_data(const dqueue_node *it, void *user_data)
{
    struct tmp_data *data = dqueue_data(it, struct tmp_data, node);

    int *user_int = (int *)user_data;

    return data->data == *user_int;
}



TEST(test_dqueue_find2)
{
    DECLARE_DQUEUE(dqueue);

    const int COUNT_NODES = 100;
    int i;
    struct tmp_data   nodes[COUNT_NODES];
    dqueue_node *f;


    for(i=0; i < COUNT_NODES; i++)
    {
        nodes[i].data = i;
        dqueue_push_back(&nodes[i].node, &dqueue);
    }



    for(i=0; i < COUNT_NODES; i++)
    {
        f = dqueue_find2(dqueue_begin(&dqueue), dqueue_end(&dqueue), pred_data, &i);

        TEST_ASSERT( f == &nodes[i].node );
    }

    i = -100;
    f = dqueue_find2(dqueue_begin(&dqueue), dqueue_end(&dqueue), pred_data, &i);

    TEST_ASSERT( f == dqueue_end(&dqueue) );



    TEST_PASS(NULL);
}



ptest_func tests[] =
{
    test_dqueue_empty,
    test_dqueue_is_first,
    test_dqueue_is_last,
    test_dqueue_is_singular,
    test_dqueue_size,
    test_dqueue_del,
    test_dqueue_pop_front,
    test_dqueue_pop_back,
    test_dqueue_replace_init,
    test_dqueue_move_to_front,
    test_dqueue_move_to_back,
    test_dqueue_rotate_left,
    test_dqueue_rotate_right,
    test_dqueue_splice_front,
    test_dqueue_splice_back,
    test_dqueue_reverse,
    test_dqueue_swap,

    //Get Data from node
    test_dqueue_data,
    test_dqueue_data_or_null,
    test_dqueue_first_data,
    test_dqueue_last_data,

    //Iterator
    test_dqueue_citer,
    test_dqueue_criter,
    test_dqueue_iter,
    test_dqueue_riter,
    test_dqueue_data_citer,
    test_dqueue_data_criter,
    test_dqueue_data_iter,
    test_dqueue_data_riter,

    //Algorithm
    test_dqueue_for_each,
    test_dqueue_min,
    test_dqueue_max,
    test_dqueue_minmax,
    test_dqueue_find,
    test_dqueue_find2,
};



MAIN_TESTS(tests)
