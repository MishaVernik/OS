using Lab4.AVL;
using Lab4.RBTree;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        class TreeNodeAVL
        {
            public TreeNodeAVL(int val)
            {
                this.val = val;
            }
            public TreeNodeAVL left;
            public TreeNodeAVL right;

            public int val;
        }
        void PrintTree(AVLTree<string>.AVLTreeNode root, TreeNode treeViewRoot)
        {
            if (root == null) return;
            if (treeViewRoot == null)
            {
                treeViewRoot = new TreeNode(root.Value);
            }
            else if (root.Value != null)
            {
                treeViewRoot.Text = root.Value;
            }
            bool left = false;
            bool right = false;
            if (root.LeftHand != null && root.LeftHand.Value != null)
            {
                treeViewRoot.Nodes.Add(root.LeftHand.Value);
                left = true;
            }
            else
            {
                treeViewRoot.Nodes.Add("null");
            }
            if (root.RightHand != null && root.RightHand.Value != null)
            {
                treeViewRoot.Nodes.Add(root.RightHand.Value);
                right = true;
            }
            else
            {
                treeViewRoot.Nodes.Add("null");
            }
            PrintTree(root.LeftHand, left ? treeViewRoot.Nodes[0] : null);
            PrintTree(root.RightHand, right ? treeViewRoot.Nodes[1] : null);
        }
        void PrintTree(RedBlackTreeNode<Int32, string> root, TreeNode treeViewRoot)
        {
            if (root == null) return;
            if (treeViewRoot == null)
            {
                treeViewRoot = new TreeNode(root.Value);
            }
            else if (root.Value != null)
            {
                treeViewRoot.Text = root.Value;
            }
            bool left = false;
            bool right = false;
            if (root.Left != null && root.Left.Value != null)
            {
                treeViewRoot.Nodes.Add(root.Left.Value);
                left = true;
            }
            else
            {
                treeViewRoot.Nodes.Add("null");
            }
            if (root.Right != null && root.Right.Value != null)
            {
                treeViewRoot.Nodes.Add(root.Right.Value);
                right = true;
            }
            else
            {
                treeViewRoot.Nodes.Add("null");
            }
            PrintTree(root.Left, left ? treeViewRoot.Nodes[0] : null);
            PrintTree(root.Right, right ? treeViewRoot.Nodes[1] : null);
        }

        int nodes = 0;
        TreeNodeAVL AddValueToTree(TreeNodeAVL root, int val)
        {
            if (root == null)
            {
                return new TreeNodeAVL(val); ;
            }
            if (root.val > val)
                root.left = AddValueToTree(root.left, val);
            else
                root.right = AddValueToTree(root.right, val);
            return root;
        }
        RedBlackTree<int, string> redBlackTree = new RBTree.RedBlackTree<int, string>();
        AVLTree<string> aVLTree = new AVL.AVLTree<string>();
        private void btnAdd_Click(object sender, EventArgs e)
        {
            
            if (textBox.TextLength == 3)
            {
                //redBlackTree.Add(nodes++, textBox.Text);
                aVLTree.Add(textBox.Text);
                treeView.Nodes.Clear();
                treeView.Nodes.Add(redBlackTree.Root.Value);
                PrintTree(aVLTree.RootNode, treeView.Nodes[0]);

                treeView.ExpandAll();
                listBox.Items.Add(textBox.Text);
                textBox.Text = "";
            }
            else
            {
                 
            }
            
            //TreeNodeAVL root = new TreeNodeAVL(1);
            ////root.left = new TreeNodeAVL(2);
            ////root.right = new TreeNodeAVL(3);
            ////root.right.left = new TreeNodeAVL(4);
            ////root.left.left = new TreeNodeAVL(5);
            //AddValueToTree(root, 12);
            //AddValueToTree(root, 13);
            //AddValueToTree(root, 14);
            //AddValueToTree(root, 15);
            //AddValueToTree(root, 16);
            //AddValueToTree(root, 22);
            //AddValueToTree(root, 100);
            //AddValueToTree(root, 1);
            //AddValueToTree(root, 4);
            //AddValueToTree(root, -12);
            //AddValueToTree(root, -122);

           
        }

        private void btnDeleteAll_Click(object sender, EventArgs e)
        {
            aVLTree = new AVLTree<string>();
            redBlackTree = new RedBlackTree<int, string>();
            treeView.Nodes.Clear();
            treeView.ExpandAll();
            richTextBox.Text = "";
            listBox.Items.Clear();
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            var selected = listBox.SelectedItem.ToString();
            if (aVLTree.Remove(selected) == true)
            {
                // deleted;
                treeView.Nodes.Clear();
                treeView.Nodes.Add(aVLTree.RootNode.Value);
                PrintTree(aVLTree.RootNode, treeView.Nodes[0]);
                treeView.ExpandAll();

                listBox.Items.Remove(selected);
            }
        }

        private void btnFind_Click(object sender, EventArgs e)
        {
                var selected = listBox.SelectedItem.ToString();
            var path = aVLTree.FindPathToNodeFromRoot(selected);
            if (path != null)
                richTextBox.Text = string.Join(" -> ", path.ToArray());
            
        }
    }
}
