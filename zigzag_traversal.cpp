#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>
#include <iterator>

class TreeNode {
    public:
        TreeNode(int value) : value_(value) {}

        void AddChild(std::unique_ptr<TreeNode> child) {
            children_.push_front(std::move(child));
        }

        void ZigzagPrint() const {
            std::stack<const TreeNode*> stack;
            std::stack<const TreeNode*> new_stack;
            const TreeNode* current = this;
            stack.push(current);
            std::stack<const TreeNode*>* stack_it = &stack;
            std::stack<const TreeNode*>* new_stack_it = &new_stack;
            bool reverse = false;
            while(true) {
                std::cout << "stack It : " << stack_it->size() << " new stack it " << new_stack_it->size() <<  "reverse: " << reverse << std::endl;
                while (!stack_it->empty()) {
                    const TreeNode* pointer  = stack_it->top();
                    stack_it->pop();
                    std::cout << "Node Value: " << pointer->value_ << std::endl;
                    auto stack_populator = [new_stack_it] (const std::unique_ptr<TreeNode>& element) {
                        const TreeNode* t = element.get();
                        new_stack_it->push(t);
                    };
                    if (reverse) {
                        std::for_each(std::rbegin(pointer->children_), std::rend(pointer->children_), stack_populator);
                    } else {
                        std::for_each(std::begin(pointer->children_), std::end(pointer->children_), stack_populator);
                    }
                }
                if (new_stack_it->empty()) return;
                std::cout << "Before stack It : " << stack_it->size() << " new stack it " << new_stack_it->size() <<  "reverse: " << reverse << std::endl;
                
                std::stack<const TreeNode*>* temp = new_stack_it;
                new_stack_it = stack_it;
                stack_it = temp;
                reverse = !reverse;
            }
        }

    private:
        const int value_;
        std::list<std::unique_ptr<TreeNode>> children_;
};

int main()
{
    TreeNode node(1);
    std::unique_ptr<TreeNode> p12(new TreeNode(12));
    std::unique_ptr<TreeNode> p31(new TreeNode(31));
    std::unique_ptr<TreeNode> p32(new TreeNode(32));
    p12->AddChild(std::move(p32));
    p12->AddChild(std::move(p31));
    node.AddChild(std::move(p12));
    std::unique_ptr<TreeNode> p11(new TreeNode(11));
    std::unique_ptr<TreeNode> p21(new TreeNode(21));
    std::unique_ptr<TreeNode> p22(new TreeNode(22));
    p11->AddChild(std::move(p22));
    p11->AddChild(std::move(p21));
    node.AddChild(std::move(p11));
    node.ZigzagPrint();

    return 0;
}
