#include "ASTNode.hpp"
#include "../../lexer/tokens/Token.hpp"

/**
 * @brief Construct a new ASTNode:: ASTNode object
 * 
 * Creates a new ASTNode object with the left and right nodes set to `nullptr` and the op set to `op`
 * 
 * @param[in] op The Token object to store in the node 
 * 
 * @see Token
 */
ASTNode::ASTNode(Token op){
    this->left = nullptr;
    this->right = nullptr;
    this->op = op;
}


/**
 * @brief Construct a new ASTNode:: ASTNode object
 * 
 * Creates a new ASTNode object with the left and right nodes set to `left` and `right` respectively, and the op set to `op`
 * 
 * @param[in] op The Token object to store in the node 
 * @param[in] left The left child node of the current node
 * @param[in] right The right child node of the current node
 * 
 * @see Token
 */
ASTNode::ASTNode(Token op, ASTNode* left, ASTNode* right){
    this->left = left;
    this->right = right;
    this->op = op;
}

/**
 * @brief Add a child node to the current node
 * 
 * Adds a child node to the current node, if the left child is `nullptr`, it sets the left child to `child`, 
 * if the right child is `nullptr`, it sets the right child to `child`
 * 
 * @param[in] child The child node to add to the current node
 */
void ASTNode::addChild(ASTNode* child){
    if(this->left == nullptr){
        this->left = child;
    } else if(this->right == nullptr){
        this->right = child;
    }
}

/**
 * @brief Set the operator of the current node
 * 
 * Sets the operator of the current node to `op`
 * 
 * @param[in] op The operator to set the current node to
 * 
 * @see Token
 */
void ASTNode::setOp(Token op){
    this->op = op;
}

/**
 * @brief Get the operator of the current node
 * 
 * Returns the operator of the current node
 * 
 * @return Token The operator of the current node
 * 
 * @see Token
 */
Token ASTNode::getOp(){
    return this->op;
}

/**
 * @brief Get the left child of the current node
 * 
 * Returns the left child of the current node
 * 
 * @return ASTNode* The left child of the current node
 */
ASTNode* ASTNode::getLeft(){
    return this->left;
}

/**
 * @brief Get the right child of the current node
 * 
 * Returns the right child of the current node
 * 
 * @return ASTNode* The right child of the current node
 */
ASTNode* ASTNode::getRight(){
    return this->right;
}

/**
 * @brief Convert the current node to a string
 * 
 * Converts the current node to a string by checking if the left and right children are `nullptr`, if they are, it returns the operator value,
 * if the left child is not `nullptr` and the right child is `nullptr`, it returns the operator value and the left child as a string, if the left and right
 * children are not `nullptr`, it returns the left child, the operator value, and the right child as a string
 * 
 * @return std::string The current node as a string
 */
std::string ASTNode::toString(){
    if(this->left == nullptr && this->right == nullptr){
        return this->op.value;
    } else if(this->left != nullptr && this->right == nullptr){
        return this->op.value + "(" + this->left->toString() + ")";
    }else {
        return "(" + this->left->toString() + this->op.value + this->right->toString() + ")";
    }
}

/**
 * @brief Destroy the ASTNode:: ASTNode object
 * 
 * Deletes the left and right children of the current node allowing for the deletion of the entire tree
 */
ASTNode::~ASTNode(){
    delete this->left;
    delete this->right;
}

