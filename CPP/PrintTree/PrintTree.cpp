#include <iostream>

#include "lib/node.hpp"
#include "lib/queue.hpp"

//  Forward declarations
namespace AO {

    using std::cout;

    void testSharedPtr();
    void testQueue();

    void runTests()
    {
        testSharedPtr();
        testQueue();
    }

    typedef node_t<int> inode_t;
    void printTree(const inode_t& root)
    {
        size_t level_num = 0;
        queue_t<inode_t> q1;
        queue_t<inode_t> q2;

        queue_t<inode_t>* pq1 = &q1;
        queue_t<inode_t>* pq2 = &q2;
        
        q1.push_back(root);

        while (!pq1->is_empty())
        {
            std::cout << "\n print level " << level_num << ": ";
            while (!pq1->is_empty())
            {
                
                const inode_t& inode = pq1->get_front();
                std::cout << " " << inode.val << ", ";
                if (inode.left)
                    pq2->push_back(*inode.left.get());

                if (inode.right)
                    pq2->push_back(*inode.right.get());

                pq1->pop_front();
            }
            ++level_num;
            
            if (pq1 == &q1)
            {
                pq2 = &q1;
                pq1 = &q2;
            }
            else
            {
                pq1 = &q1;
                pq2 = &q2;
            }
        }
    }

    void initTree1(inode_t& root)
    {
        inode_t l31(31);
        inode_t l32(32);
        inode_t l33(33);
        inode_t l34(34);
        inode_t l35(35);
        inode_t l36(36);
        inode_t l37(37);
        inode_t l38(38);

        inode_t l21(21);
        l21.left = make_shared(l31);
        l21.right = make_shared(l32);

        inode_t l22(22);
        l22.left = make_shared(l33);
        l22.right = make_shared(l34);

        inode_t l23(23);
        l23.left = make_shared(l35);
        l23.right = make_shared(l36);

        inode_t l24(24);
        l24.left = make_shared(l37);
        l24.right = make_shared(l38);

        inode_t l11(11);
        l11.left = make_shared(l21);
        l11.right = make_shared(l22);

        inode_t l12(12);
        l12.left = make_shared(l23);
        l12.right = make_shared(l24);

        root.left = make_shared(l11);
        root.right = make_shared(l12);
    }

    void initTree2(inode_t& root)
    {
        inode_t l31(31);
        inode_t l32(32);
        inode_t l33(33);
        inode_t l34(34);
        inode_t l35(35);
        inode_t l36(36);
        inode_t l37(37);
        inode_t l38(38);

        inode_t l21(21);
        l21.left = make_shared(l31);
        //l21.right = make_shared(l32);

        inode_t l22(22);
        //l22.left = make_shared(l33);
        l22.right = make_shared(l34);

        inode_t l23(23);
        l23.left = make_shared(l35);
        //l23.right = make_shared(l36);

        inode_t l24(24);
        //l24.left = make_shared(l37);
        l24.right = make_shared(l38);

        inode_t l11(11);
        l11.left = make_shared(l21);
        l11.right = make_shared(l22);

        inode_t l12(12);
        l12.left = make_shared(l23);
        l12.right = make_shared(l24);

        root.left = make_shared(l11);
        root.right = make_shared(l12);
    }

    void initTree3(inode_t& root)
    {
        inode_t l31(31);
        inode_t l32(32);
        inode_t l33(33);
        inode_t l34(34);
        inode_t l35(35);
        inode_t l36(36);
        inode_t l37(37);
        inode_t l38(38);

        inode_t l21(21);
        l21.left = make_shared(l31);
        l21.right = make_shared(l32);

        inode_t l22(22);
        l22.left = make_shared(l33);
        l22.right = make_shared(l34);

        inode_t l23(23);
        l23.left = make_shared(l35);
        l23.right = make_shared(l36);

        inode_t l24(24);
        l24.left = make_shared(l37);
        l24.right = make_shared(l38);

        inode_t l11(11);
        l11.left = make_shared(l21);
        l11.right = make_shared(l22);

        inode_t l12(12);
        l12.left = make_shared(l23);
        l12.right = make_shared(l24);

        root.left = make_shared(l11);
        //root.right = make_shared(l12);
    }

    void testPrintTree()
    {
        cout << "\nCase 1:";
        AO::inode_t root(100);
        AO::printTree(root);

        cout << "\nCase 2:";
        root = inode_t();
        AO::initTree1(root);
        AO::printTree(root);

        cout << "\nCase 3:";
        root = inode_t();
        AO::initTree2(root);
        AO::printTree(root);

        cout << "\nCase 4:";
        root = inode_t();
        AO::initTree3(root);
        AO::printTree(root);
    }
}


int main()
{
    AO::testPrintTree();
}
