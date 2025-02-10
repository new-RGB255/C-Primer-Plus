#pragma once
#ifndef _RB_TREE_H_
#define _RB_TREE_H_
#include "fakedstl.h"
#define  _SGI_STLNO_ARROW_OPERATOR

using _rb_tree_colour_type = bool;
const _rb_tree_colour_type _rb_tree_red = false;
const _rb_tree_colour_type _rb_tree_black = true;

struct _rb_tree_node_base {
	using colour_type = _rb_tree_colour_type;
	using base_ptr = _rb_tree_node_base*;

	colour_type colour;
	colour_type doubleBlack = false; // 通过双黑标记在删除时表示通过该节点的所有路径都违反黑路同性质
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	_rb_tree_node_base(base_ptr par = nullptr, base_ptr le = nullptr, base_ptr ri = nullptr,
		colour_type col = _rb_tree_red) :parent(par), left(le), right(ri), colour(col) {}

	virtual ~_rb_tree_node_base() {}

	static base_ptr minimum(base_ptr x) {
		while (x->left) {
			x = x->left;
		}
		return x;
	}

	static base_ptr maximum(base_ptr x) {
		while (x->right) {
			x = x->right;
		}
		return x;
	}
};

template<class _Value>
struct _rb_tree_node : public _rb_tree_node_base {
	using value = _Value;
	using link_type = _rb_tree_node<value>*;
	using colour_type = _rb_tree_colour_type;
	using base_ptr = _rb_tree_node_base*;

	value value_field;

	_rb_tree_node() :_rb_tree_node_base() {}

	_rb_tree_node(value val, base_ptr par = nullptr, base_ptr le = nullptr, base_ptr ri = nullptr,
		colour_type col = _rb_tree_red) :value_field(val), _rb_tree_node_base(par, le, ri, col) {}

	~_rb_tree_node() {}
};

struct _rb_tree_base_iterator {
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using base_iterator = _rb_tree_base_iterator;
	using base_ptr = _rb_tree_node_base*;

	base_ptr node;

	void increment() {
		if (node->colour == _rb_tree_red &&
			node->parent->parent == node) {
			/*
			*	迭代器指向end()时返回RB_tree中的最小值
			*/
			node = node->left;
		}
		else if (node->right) {
			/*
			*	存在右子节点,向左找最小的节点
			*/
			node = node->right;
			while (node->left) {
				node = node->left;
			}
		}
		else {
			/*
			*	没有右子节点,找出其父节点
			*	若现行节点本身是个右子节点,就一直上溯
			*	直到“不为右子节点为止”
			*/
			base_ptr ptr = node->parent;
			while (node == ptr->right) {
				node = ptr;
				ptr = ptr->parent;
			}
			/*
			*	若此时的右子节点不为此时的父节点,则此时的父节点为解答
			*	否则原本node节点指向RB_tree中的最大节点,此时迭代器指向end()
			*/
			if (node->right != ptr) {
				node = ptr;
			}
		}
	}

	void decrement() {
		if (node->colour == _rb_tree_red &&
			node->parent->parent == node) {
			/*
			*	迭代器指向end()时返回RB_tree中的最大值
			*/
			node = node->right;
		}
		else if (node->left) {
			/*
			*	存在左子节点,向左子树的右分支找最大的节点
			*/
			base_ptr ptr = node->left;
			while (ptr->right) {
				ptr = ptr->right;
			}
			node = ptr;
		}
		else {
			/*
			*	没有左子节点,找出其父节点
			*	若现行节点本身是个左子节点,就一直上溯
			*	直到“不为左子节点为止”
			*/
			base_ptr ptr = node->parent;
			while (node == ptr->left) {
				node = ptr;
				ptr = ptr->parent;
			}
			node = ptr;
		}
	}
};

//RB_tree iterator
template<class Val, class Ref, class Ptr>
struct _rb_tree_iterator :public _rb_tree_base_iterator {
	using value_type = Val;
	using reference = Ref;
	using pointer = Ptr;
	using iterator = _rb_tree_iterator<Val, Val&, Val*>;
	using const_iterator = _rb_tree_iterator<Val, const Val&, const Val*>;
	using self = _rb_tree_iterator<Val, Ref, Ptr>;
	using link_type = _rb_tree_node<Val>*;

	_rb_tree_iterator() {}
	explicit _rb_tree_iterator(link_type x) { node = x; }
	_rb_tree_iterator(const iterator& it) { node = it.node; }
	

	reference operator*() const { return link_type(node)->value_field; }
#ifdef _SGI_STLNO_ARROW_OPERATOR
	pointer operator->() const { return&(operator*()); }
#endif // !_SGI_STLNO_ARROW_OPERATOR

	self& operator++() { increment(); return *this; }
	self operator++(int) {
		self tmp = *this;
		increment();
		return tmp;
	}

	self& operator--() { decrement(); return *this; }
	self operator--(int) {
		self tmp = *this;
		decrement();
		return tmp;
	}

	bool operator!=(const iterator& it) { return (*this).node != it.node; }
	bool operator==(const iterator& it) { return (*this).node == it.node; }

	self& operator=(const iterator& it) {
		if (this == &it) return *this;
		this->node = it.node;
		return *this;
	}
};

class none_existed :public std::exception {
public:
	none_existed() {}
	~none_existed() {}
	void what() { std::cerr << "none found" << std::endl; }
};

inline void _rb_tree_rebalance(_rb_tree_node_base* x, _rb_tree_node_base*& root);
inline void _rb_tree_rotate_left(_rb_tree_node_base* x, _rb_tree_node_base*& root);
inline void _rb_tree_rotate_right(_rb_tree_node_base* x, _rb_tree_node_base*& root);

namespace fakedSTL {
	template<class Key, class Value, class KeyOfValue, class Compare = std::less<Key>>
	class RB_tree {
	protected:
		using void_pointer = void*;
		using colour_type = _rb_tree_colour_type;
		using base = _rb_tree_node_base;
		using base_ptr = _rb_tree_node_base*;
		using rb_tree_node = _rb_tree_node<Value>;
	public:
		using key_type = Key;
		using value_type = Value;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using difference_type = std::ptrdiff_t;
		using link_type = rb_tree_node*;
		using self = RB_tree<Key, Value, KeyOfValue, Compare>;
	protected:
		/*
		*	创建,拷贝和删除节点
		*/

		link_type create_node(const value_type& x) { 
			try {
				link_type tmp = new rb_tree_node(x);
				if (tmp != nullptr) {
					return tmp;
				}
				std::bad_alloc bad;
				throw bad;
			}
			catch (const std::exception& bad) {
				std::ignore = bad.what();
			}
		}

		void delete_node(link_type p) { delete p; }

		link_type clone_node(link_type x) { // copy value and colour of a node
			link_type tmp = create_node(x->value_field);
			tmp->colour = x->colour;
			return tmp;
		}

		void destroy_node(link_type p) {
			delete_node(p);
		}
	protected:
		size_type node_count; // 节点个数
		link_type header; // 迭代器实现技巧,该节点为RB_tree的end(),与根节点互为父节点
		Compare key_compare; // 键的大小比较准则, function object

		// 获取header的成员

		link_type& root() const { return (link_type&)(header->parent); } // 获取根节点
		link_type& leftmost() const { return (link_type&)(header->left); } // 获取最小值
		link_type& rightmost() const { return (link_type&)(header->right); } // 获取最大值

		// 获取节点x的成员

		static link_type& parent(link_type x) { return (link_type&)(x->parent); }
		static link_type& left(link_type x) { return (link_type&)(x->left); }
		static link_type& right(link_type x) { return (link_type&)(x->right); }
		static reference value(link_type x) { return x->value_field; }
		static const key_type& key(link_type x) { return KeyOfValue()(value(x)); }
		static colour_type& colour(link_type x) { return (colour_type&)(x->colour); }
		static colour_type& doubleblack(link_type x) { return (colour_type&)(x->doubleBlack); }
		static link_type& parent(base_ptr x) { return (link_type&)(x->parent); }
		static link_type& left(base_ptr x) { return (link_type&)(x->left); }
		static link_type& right(base_ptr x) { return (link_type&)(x->right); }
		static reference value(base_ptr x) { return link_type(x)->value_field; }
		static const key_type& key(base_ptr x) { return KeyOfValue()(value(link_type(x))); }
		static colour_type& colour(base_ptr x) { return (colour_type&)(link_type(x)->colour); }
		static colour_type& doubleblack(base_ptr x) { return (colour_type&)(link_type(x)->doubleBlack); }

		// 获取极大值和极小值

		static link_type maximum(link_type x) { return (link_type)_rb_tree_node_base::maximum(x); }
		static link_type minimum(link_type x) { return (link_type)_rb_tree_node_base::minimum(x); }
	public:
		//iterator
		using iterator = _rb_tree_iterator<value_type, reference, pointer>;
	private:
		iterator _insert(base_ptr _x, base_ptr _y, const value_type& v) {
			// 参数_x为新值插入点,参数_y为插入点之父节点,参数v为新值

			link_type x = link_type(_x);
			link_type y = link_type(_y);
			link_type newnode;
			if (y == header || x != nullptr || key_compare(KeyOfValue()(v), key(y))) {
				newnode = create_node(v);
				left(y) = newnode;
				if (y == header) {
					root() = newnode;
					rightmost() = newnode;
				}
				else if (y == leftmost()) {
					leftmost() = newnode;
				}
			}
			else {
				newnode = create_node(v);
				right(y) = newnode;
				if (y == rightmost()) {
					rightmost() = newnode;
				}
			}
			parent(newnode) = y;
			// 新节点的颜色将在_rb_tree_rebalance()中调整
			_rb_tree_rebalance(newnode, header->parent);
			++node_count;
			return iterator(newnode);
		}

		void _copy(link_type x, link_type p) {
			if (p == nullptr) return;
			link_type newnode = clone_node(p);
			newnode->parent = x;
			if (x == header) { // 复制节点为根节点时
				x->parent = newnode;
				x = parent(x);
			}
			else if (p == p->parent->left) { // 复制节点在左支时
				x->left = newnode;
				x = left(x);
			}
			else { // 复制节点在右支时
				x->right = newnode;
				x = right(x);
			}
			_copy(x, link_type(p->left));
			_copy(x, link_type(p->right));
		}

		void _erase(iterator iter) {
			link_type x = link_type(iter.node);
			iterator it = iter;
			auto delete_alone_leftchild = [&](link_type d) {
				// d为删除点
				if (d == rightmost()) { // 删除的是最大值,更改最大值
					--it;
					rightmost() = link_type(it.node);
				}
				if (d == root()) {
					leftmost() = left(d);
					rightmost() = left(d);
					parent(parent(d)) = left(d);
				}
				else if (d == left(parent(d))) left(parent(d)) = left(d);
				else right(parent(d)) = left(d);
				parent(left(d)) = parent(d);
				colour(left(d)) = _rb_tree_black;
				delete_node(d);
				};
			auto delete_alone_rightchild = [&](link_type d) {
				// d为删除点
				if (d == leftmost()) { // 删除的是最小值,更改最小值
					++it;
					leftmost() = link_type(it.node);
				}
				if (d == root()) {
					leftmost() = right(d);
					rightmost() = right(d);
					parent(parent(d)) = right(d);
				}
				else if (d == left(parent(d))) left(parent(d)) = right(d);
				else right(parent(d)) = right(d);
				parent(right(d)) = parent(d);
				colour(right(d)) = _rb_tree_black;
				delete_node(d);
				};
			auto delete_none_child = [&](link_type d) {
				// d为删除点
				if (d == leftmost()) { // 删除的是最小值,更改最小值
					++it;
					leftmost() = link_type(it.node);
				}
				else if (d == rightmost()) { // 删除的是最大值,更改最大值
					--it;
					rightmost() = link_type(it.node);
				}
				if (colour(d) == _rb_tree_red) { // 若d为红节点,删除后无需任何调整
					if (left(parent(d)) == d) { // d在左支上
						left(parent(d)) = nullptr;
					}
					else { // d在右支上
						right(parent(d)) = nullptr;
					}
					delete_node(d);
				} 
				else { // d为黑节点(除根节点外),必然有兄弟,不然违反黑路同
					if (d == root()) { // 删除点为根节点
						leftmost() = nullptr;
						rightmost() = nullptr;
						parent(parent(d)) = nullptr;
						delete_node(d);
					}
					else { // 其它
						link_type tmp = d;
						doubleblack(d) = true;
						if (left(parent(d)) == d) { // d在左支上
							while (doubleblack(d)) {
								if (colour(right(parent(d))) == _rb_tree_red) { // 兄弟是红色
									/*
									*  兄父变色(兄变黑,父变红),朝双黑旋转
									*/
									colour(right(parent(d))) = _rb_tree_black;
									colour(parent(d)) = _rb_tree_red;
									_rb_tree_rotate_left(d->base::parent, header->base::parent); // 旋转后保持双黑节点继续判断
								}
								else { // 兄弟是黑色
									if (left(right(parent(d))) != nullptr ||
										right(right(parent(d))) != nullptr) { // 兄弟至少有一个红孩子(先保证节点不为空)
										/*
										*	(LL,RR,LR,RR)变色+旋转
										*	(双黑变单黑)
										*/
										if (right(right(parent(d))) != nullptr &&
											colour(right(right(parent(d)))) == _rb_tree_red) { // RR型
											/*
											*	令RR型节点从上到下依次为g(grandparent),p(parent),c(child)
											*	则变色顺序为(c变p,p变g,g变黑)
											*/
											colour(right(right(parent(d)))) = colour(right(parent(d)));
											colour(right(parent(d))) = colour(parent(d));
											colour(parent(d)) = _rb_tree_black;
											_rb_tree_rotate_left(d->base::parent, header->base::parent);
											doubleblack(d) = false;
										}
										else { // RL型
											/*
											*	令RL型节点从上到下依次为g(grandparent),p(parent),c(child)
											*	则变色顺序为(c变g,g变黑),p不变
											*/
											colour(left(right(parent(d)))) = colour(parent(d));
											colour(parent(d)) = _rb_tree_black;
											_rb_tree_rotate_right(d->base::parent->left, header->base::parent);
											_rb_tree_rotate_left(d->base::parent, header->base::parent);
											doubleblack(d) = false;
										}
									}
									else { // 兄弟的孩子都是黑色(包括空节点,因为空节点定义为黑)
										/*
										*	兄弟变红,双黑上移
										*	(遇红或根变单黑)
										*/
										colour(right(parent(d))) = _rb_tree_red;
										doubleblack(d) = false;
										d = parent(d);
										doubleblack(d) = true;
										if (colour(d) == _rb_tree_red || d == root()) {
											doubleblack(d) = false;
											colour(d) = _rb_tree_black;
										}
									}
								}
							}
						}
						else { // d在右支上
							while (doubleblack(d)) {
								if (colour(left(parent(d))) == _rb_tree_red) { // 兄弟是红色
									/*
									*  兄父变色(兄变黑,父变红),朝双黑旋转
									*/
									colour(left(parent(d))) = _rb_tree_black;
									colour(parent(d)) = _rb_tree_red;
									_rb_tree_rotate_right(d->base::parent, header->base::parent); // 旋转后保持双黑节点继续判断
								}
								else { // 兄弟是黑色
									if (left(left(parent(d))) != nullptr ||
										right(left(parent(d))) != nullptr) { // 兄弟至少有一个红孩子(先保证节点不为空)
										/*
										*	(LL,RR,LR,RR)变色+旋转
										*	(双黑变单黑)
										*/
										if (left(left(parent(d))) != nullptr &&
											colour(left(left(parent(d)))) == _rb_tree_red) { // LL型
											/*
											*	令LL型节点从上到下依次为g(grandparent),p(parent),c(child)
											*	则变色顺序为(c变p,p变g,g变黑)
											*/
											colour(left(left(parent(d)))) = colour(left(parent(d)));
											colour(left(parent(d))) = colour(parent(d));
											colour(parent(d)) = _rb_tree_black;
											_rb_tree_rotate_right(d->base::parent, header->base::parent);
											doubleblack(d) = false;
										}
										else { // LR型
											/*
											*	令LR型节点从上到下依次为g(grandparent),p(parent),c(child)
											*	则变色顺序为(c变g,g变黑),p不变
											*/
											colour(right(left(parent(d)))) = colour(parent(d));
											colour(parent(d)) = _rb_tree_black;
											_rb_tree_rotate_left(d->base::parent->left, header->base::parent);
											_rb_tree_rotate_right(d->base::parent, header->base::parent);
											doubleblack(d) = false;
										}
									}
									else { // 兄弟的孩子都是黑色(包括空节点,因为空节点定义为黑)
										/*
										*	兄弟变红,双黑上移
										*	(遇红或根变单黑)
										*/
										colour(left(parent(d))) = _rb_tree_red;
										doubleblack(d) = false;
										d = parent(d);
										doubleblack(d) = true;
										if (colour(d) == _rb_tree_red || d == root()) {
											doubleblack(d) = false;
											colour(d) = _rb_tree_black;
										}
									}
								}
							}
						}
						if (left(parent(tmp)) == tmp) { // tmp在左支上
							left(parent(tmp)) = nullptr;
						}
						else { // tmp在右支上
							right(parent(tmp)) = nullptr;
						}
						delete_node(tmp);
					}
				}
				};
			if (left(x) && right(x)) { // 左右子树都有
				link_type prev = maximum(left(x)); // 找到删除点的前继节点
				value(x) = value(prev);
				if (prev == leftmost()) leftmost() = x; // 若删除点的前继节点为最小值,更改最小值
				if (left(prev)) { 
					delete_alone_leftchild(prev); 
				}
				else {
					delete_none_child(prev);
				}
			}
			else if (left(x)) { // 只有左孩子
				delete_alone_leftchild(x);
			}
			else if (right(x)) { // 只有右孩子
				delete_alone_rightchild(x);
			}
			else { // 没有孩子
				delete_none_child(x);
			}
			--node_count;
		}

		void init() {
			try {
				header = new rb_tree_node();
				if (header == nullptr) {
					std::bad_alloc bad;
					throw bad;
				}
				leftmost() = header;
				rightmost() = header;
			}
			catch (const std::exception& bad) {
				std::ignore = bad.what();
			}
		}

		void clear(link_type p) {
			if (p == nullptr) return;
			clear(left(p));
			clear(right(p));
			self::destroy_node(p);
		}
	public:
		/*
		*	构造与内存管理
		*/

		RB_tree(const Compare& comp = Compare()) :node_count(0), key_compare(comp) { init(); }

		RB_tree(const self& rb) {
			node_count = rb.node_count;
			key_compare = rb.key_comp();
			init();
			_copy(header, link_type(rb.header->parent));
			leftmost() = minimum(root());
			rightmost() = maximum(root());
		}

		~RB_tree() {
			if (!empty()) clear(root());
			self::destroy_node(header);
		}

		self& operator=(const self& rb) {
			if (this == &rb) return *this;
			clear();
			_copy(header, link_type(rb.header->parent));
			leftmost() = minimum(root());
			rightmost() = maximum(root());
			return *this;
		}
	public:
		Compare key_comp() const { return key_compare; }
		iterator begin() { return iterator(leftmost()); }
		iterator end() { return iterator(header); }
		bool empty() const { return node_count == 0; }
		size_type size() const { return node_count; }
		size_type max_size() const { return size_type(-1); }
	public:
		iterator insert_equal(const value_type& v) {
			link_type y = header;
			link_type x = root(); // 从根节点开始
			while (x) { // 从根节点开始,向下寻找适当的插入点
				y = x;
				x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
			}
			return _insert(x, y, v);
		}

		std::pair<iterator, bool> insert_unique(const value_type& v) {
			/*
			*	插入新值:节点键值不允许重复,若重复则插入无效
			*	注意,返回值是一个pair,其中pair.first是一个RB_tree的迭代器,指向新增节点
			*	pair.second表示插入是否成功
			*/

			link_type y = header;
			link_type x = root(); // 从根节点开始
			bool compare = true;
			while (x) { // 从根节点开始,向下寻找适当的插入点
				y = x;
				compare = key_compare(KeyOfValue()(v), key(x));
				x = compare ? left(x) : right(x);
			}
			// 退出while循环后y所指即为插入点之父节点(此时的它必为叶节点)

			iterator j = iterator(y); // 令迭代器j指向插入点之父节点y
			if (compare) { // 若退出while循环时compare为true,表示新键值<插入点之父节点的键值,插入于左侧
				if (j == begin()) { // 若插入点之父节点为最左节点
					return std::pair<iterator, bool>(_insert(x, y, v), true);
				}
				else { // 否则插入点之父节点不为最左节点,新键值可能与前面的键值重复
					--j; // 上溯到y的父节点
				}
			}
			if (key_compare(key(j.node), KeyOfValue()(v))) { // y的父节点之键值与新键值的大小,小为真
				// 新键值不与既有节点之键值重复,执行插入操作
				return std::pair<iterator, bool>(_insert(x, y, v), true);
			}
			// 进行至此,表示新键值一定与树中既有节点之键值重复,不执行插入操作
			return std::pair<iterator, bool>(j, false);
		}

		iterator find(const key_type& k) {
			link_type target = header;
			link_type cur = root();
			while (cur) {
				if (!key_compare(key(cur), k)) {
					target = cur;
					cur = left(cur);
				}
				else {
					cur = right(cur);
				}
			}
			iterator found = iterator(target);
			return (found == end() || key_compare(k, key(found.node))) ? end() : found;
		}

		void clear() {
			if (!empty()) clear(root());
			parent(header) = nullptr;
			leftmost() = header;
			rightmost() = header;
			node_count = 0;
		}

		void erase(const key_type& k) {
			try {
				iterator iter = find(k);
				if (iter == end()) {
					none_existed ne;
					throw ne;
				}
				/*
				*	当确定找到该元素在RB_tree中的位置
				*	执行以下删除操作,该操作包含使得RB_tree恢复红黑树性质
				*	的平衡函数
				*/
				_erase(iter);
			}
			catch (const std::exception& ne) {
				std::ignore = ne.what();
			}
		}
	};
}

inline void _rb_tree_rebalance(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
	/*
	*	x为插入点,root为根节点
	*	若执行插入操作后RB_tree性质被破环(只可能违反根叶黑和不红红),则有三种调整情况:
	*	1) 插入点为根节点
	*   2) 插入点的伯父节点为红色
	*   3) 插入点的伯父节点为黑色
	*/
	while (x != root && x->parent->colour == _rb_tree_red) { // 父节点为红
		if (x->parent == x->parent->parent->left) { // 父节点为祖父节点之左节点
			_rb_tree_node_base* y = x->parent->parent->right; // 令y为伯父节点
			if (y && y->colour == _rb_tree_red) { // 伯父节点且为红
				x->parent->colour = _rb_tree_black; // 更改父节点为黑
				y->colour = _rb_tree_black; // 更改伯父节点为黑
				x->parent->parent->colour = _rb_tree_red; // 更改祖父节点为红
				x = x->parent->parent; // 使祖父节点变为迭代节点向上检查,判断RB_tree性质是否被破环
			}
			else { // 无伯父节点或伯父节点为黑
				if (x == x->parent->right) {
					x = x->parent;
					_rb_tree_rotate_left(x, root); // 第一参数为左旋点
				}
				x->parent->colour = _rb_tree_black; // 更改颜色
				x->parent->parent->colour = _rb_tree_red;
				_rb_tree_rotate_right(x->parent->parent, root); // 第一参数为右旋点
			}
		}
		else { // 父节点为祖父节点之右节点,下面的判断逻辑与父节点为左节点类似
			_rb_tree_node_base* y = x->parent->parent->left; 
			if (y && y->colour == _rb_tree_red) { // 伯父节点且为红
				x->parent->colour = _rb_tree_black; // 更改父节点为黑
				y->colour = _rb_tree_black; // 更改伯父节点为黑
				x->parent->parent->colour = _rb_tree_red; // 更改祖父节点为红
				x = x->parent->parent; // 使祖父节点变为迭代节点向上检查,判断RB_tree性质是否被破环
			}
			else { // 无伯父节点或伯父节点为黑
				if (x == x->parent->left) {
					x = x->parent;
					_rb_tree_rotate_right(x, root); // 第一参数为右旋点
				}
				x->parent->colour = _rb_tree_black; // 更改颜色
				x->parent->parent->colour = _rb_tree_red;
				_rb_tree_rotate_left(x->parent->parent, root); // 第一参数为左旋点
			}
		}
	} // while结束
	root->colour = _rb_tree_black; // 根节点永远为黑
}

inline void _rb_tree_rotate_left(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
	// x为旋转点

	_rb_tree_node_base* y = x->right; // y为旋转点的右子节点
	x->right = y->left;
	if (y->left) {
		y->left->parent = x;
	}
	// 令y完全顶替x的地位(y必须完全接替x的所有关系)
	y->parent = x->parent;
	if (x == root) { // x为根节点
		root = y;
	}
	else if (x == x->parent->left) { // x为其父节点的左子节点
		x->parent->left = y;
	}
	else { // x为其父节点的右子节点
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

inline void _rb_tree_rotate_right(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
	// x为旋转点

	_rb_tree_node_base* y = x->left; // y为旋转点的左子节点
	x->left = y->right;
	if (y->right) {
		y->right->parent = x;
	}
	// 令y完全顶替x的地位(y必须完全接替x的所有关系)
	y->parent = x->parent;
	if (x == root) { // x为根节点
		root = y;
	}
	else if (x == x->parent->right) { // x为其父节点的右子节点
		x->parent->right = y;
	}
	else { // x为其父节点的左子节点
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}


#endif // !_RB_TREE_H_
