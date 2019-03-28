/**
 * Automatic tests for the exercise on binary trees.
 *
 * @author Liad Cohen, Timor Sharabi, Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
using std::cout, std::endl;
#include "badkan.hpp"
#include "Tree.hpp"

int main() {
  ariel::Tree emptytree;
  ariel::Tree threetree;
  threetree.insert(5);
  threetree.insert(7);
  threetree.insert(3);
  ariel::Tree increasetree; //tree for increasing-order checks and tests for all combinations of binary tree test cases.
  ariel::Tree negativetree;  //tree for decreasing-order with NEGATIVE integers checks and tests for all combinations of binary tree test cases.
  ariel::Tree massivetree; //fully grown complex binary tree for all remaining test cases.

  badkan::TestCase tc("Binary tree");
  tc
  .CHECK_EQUAL (emptytree.size(), 0)
  .CHECK_OK    (emptytree.insert(5))
  .CHECK_EQUAL (emptytree.size(), 1)
  .CHECK_EQUAL (emptytree.contains(5), true)
  .CHECK_OK    (emptytree.remove(5))
  .CHECK_THROWS(emptytree.remove(5))
  .CHECK_EQUAL (emptytree.size() ,0)

  .CHECK_EQUAL (threetree.size(), 3)
  .CHECK_EQUAL (threetree.root(), 5)
  .CHECK_EQUAL (threetree.parent(3), 5) //test #10
  .CHECK_EQUAL (threetree.parent(7), 5)
  .CHECK_EQUAL (threetree.left(5), 3)
  .CHECK_EQUAL (threetree.right(5), 7)
  .CHECK_THROWS(threetree.insert(3))
  // .CHECK_OK    (threetree.print())

//Added tests:
  .CHECK_EQUAL (increasetree.size(), 0) //new tree should have size zero.
  .CHECK_OK (increasetree.insert(0)) //inserting integers in increasing order. tree should be as follows:
  //                                    0
  .CHECK_OK (increasetree.insert(1)) //   1
  .CHECK_OK (increasetree.insert(2)) //     2
  .CHECK_OK (increasetree.insert(3)) //       3
  .CHECK_EQUAL (increasetree.size(), 4) //tree size should be 4. we inserted 4 elements.
  .CHECK_THROWS (increasetree.parent(0)) //there should be no parent for node "0".
  .CHECK_EQUAL (increasetree.parent(1),0) //parent of element "1" should be the root, a.k.a  "0".
  .CHECK_THROWS (increasetree.left(3)) //there are no childs for node "3".
  .CHECK_THROWS (increasetree.right(3)) //there are no childs for node "3".
  .CHECK_THROWS (increasetree.left(0)) //there are no left-childs for the root "0".
  .CHECK_THROWS (increasetree.left(1)) //there are no left-childs for the root "1".
  .CHECK_THROWS (increasetree.left(2)) //there are no left-childs for the root "2".
  .CHECK_EQUAL (increasetree.right(0),1) //there right child of root node "0" should be "1".
  .CHECK_OK (increasetree.contains(2)) //function "contains" should pass as "2" is inside the tree.
  .CHECK_EQUAL (increasetree.contains(-1),false) //function "contains" should fail as "-1" is NOT inside the tree.
  .CHECK_OK (increasetree.root()) //function "root" should pass as there is a root for the tree.
  .CHECK_OK (increasetree.insert(10)) //inserting more elements
  .CHECK_OK (increasetree.insert(7)) //inserting element breaking the increase-tree.
  .CHECK_EQUAL (increasetree.size(), 6)
  .CHECK_EQUAL (increasetree.parent(7),10)
  .CHECK_EQUAL (increasetree.left(10),7)
  .CHECK_THROWS (increasetree.right(10))
  .CHECK_THROWS (increasetree.right(7))
  .CHECK_THROWS (increasetree.left(7))
  
  .CHECK_OK (negativetree.insert(-1)) //adding negative integers in degreasing order.
  .CHECK_OK (negativetree.insert(-2))
  .CHECK_OK (negativetree.insert(-3))
  .CHECK_EQUAL (negativetree.size(),3)  //size should be 3
  .CHECK_EQUAL (negativetree.left(-1),-2)  //left child of ROOT ("-1") node should be "-2"
  .CHECK_EQUAL (negativetree.left(-2),-3) //left child of INSIDE_NODE("-2") node should be "-3"
  .CHECK_OK (negativetree.insert(0)) //we now insert a larger-than-every-node "0" to the tree.
  .CHECK_EQUAL (negativetree.parent(0),-1) //parent of the "0" node, which we inserted last, should be the right chile of -1. thus, parent of 0 is -1.
  .CHECK_EQUAL (negativetree.right(-1),0) //explained above
  .CHECK_THROWS (negativetree.left(0)) //last-inserted node "0" should have no childs!
  .CHECK_THROWS (negativetree.right(0)) //last-inserted node "0" should have no childs!
  .CHECK_THROWS (negativetree.parent(-1)) //-1 is the root hence it should have no parent.

  .CHECK_OK (massivetree.insert(0))
  .CHECK_OK (massivetree.insert(-10))
  .CHECK_OK (massivetree.insert(-30))
  .CHECK_OK (massivetree.insert(-5))
  .CHECK_OK (massivetree.insert(-1))
  .CHECK_OK (massivetree.insert(100))
  .CHECK_OK (massivetree.insert(1))
  .CHECK_OK (massivetree.insert(200))
  .CHECK_OK (massivetree.insert(150))
  // According to insertion order, tree should look like:
  /*
                    0
            -10             100
         -30    -5       1       200
                   -1         150
  */
  .CHECK_EQUAL (massivetree.size(),9)
  .CHECK_THROWS (massivetree.parent(0)) //0 is root.
  .CHECK_EQUAL (massivetree.parent(-1),-5)
  .CHECK_EQUAL (massivetree.parent(-5),-10)
  .CHECK_EQUAL (massivetree.parent(-10),0)
  .CHECK_EQUAL (massivetree.parent(-30),-10)
  .CHECK_EQUAL (massivetree.parent(150),200)
  .CHECK_EQUAL (massivetree.parent(1),100)
  .CHECK_EQUAL (massivetree.parent(200),100)
  .CHECK_EQUAL (massivetree.left(0),-10)
  .CHECK_EQUAL (massivetree.left(-10),-30)
  .CHECK_EQUAL (massivetree.left(100),1)
  .CHECK_EQUAL (massivetree.right(0),100)
  .CHECK_EQUAL (massivetree.right(100),200)
  .CHECK_EQUAL (massivetree.right(-10),-5)
  .CHECK_EQUAL (massivetree.right(-5),-1)
  .CHECK_THROWS (massivetree.left(-30))
  .CHECK_THROWS (massivetree.left(-5))
  .CHECK_THROWS (massivetree.left(1))
  .CHECK_THROWS (massivetree.left(150))
  .CHECK_THROWS (massivetree.right(-30))
  .CHECK_THROWS (massivetree.right(1))
  .CHECK_THROWS (massivetree.right(200))
  .CHECK_THROWS (massivetree.right(150))
  .CHECK_THROWS (massivetree.insert(-30)) //insertion twice same element.
  .CHECK_OK (massivetree.remove(-30))
  .CHECK_THROWS (massivetree.remove(-30)) //double-removing.
  .CHECK_THROWS (massivetree.remove(-1000)) //removing non-existant element.
  .CHECK_THROWS (massivetree.parent(-30)) //parent of a removed element.
  .CHECK_EQUAL (massivetree.size(),8) //size should decrease to 8.
  .CHECK_THROWS (massivetree.insert(0)) //insertion of already-existant element.
  .CHECK_OK (massivetree.remove(0)); //removing root. should pick left child (-10) as root now.

  cout << "You have " << tc.right() << " right answers and " << tc.wrong() << " wrong answers so your grade is " << tc.grade() << ". Great!" << endl;
}
