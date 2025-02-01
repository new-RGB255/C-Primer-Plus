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
				node = ptr;
			}
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
	explicit _rb_tree_iterator(const iterator& it) { node = it.node; }

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
};



namespace fakedSTL {
	template<class Key, class Value, class KeyOfValue, class Compare = std::less<Key>>
	class RB_tree {
	protected:
		using void_pointer = void*;
		using colour_type = _rb_tree_colour_type;
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
				if (tmp == nullptr) {
					std::bad_alloc bad;
					throw bad;
				}
				return tmp;
			}
			catch (const std::exception& bad) {
				bad.what();
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

		link_type& root(link_type x) const { return (link_type&)(header->parent); } // 获取根节点
		link_type& leftmost(link_type x) const { return (link_type&)(header->left); } // 获取最小值
		link_type& rightmost(link_type x) const { return (link_type&)(header->right); } // 获取最大值

		// 获取节点x的成员

		static link_type& parent(link_type x) { return (link_type&)(x->parent); }
		static link_type& left(link_type x) { return (link_type&)(x->left); }
		static link_type& right(link_type x) { return (link_type&)(x->right); }
		static reference value(link_type x) { return x->value_field; }
		static const key_type& key(link_type x) { return KeyOfValue()(value(x)); }
		static colour_type& colour(link_type x) { return (colour_type&)(x->colour); }
		static link_type& parent(base_ptr x) { return (link_type&)(x->parent); }
		static link_type& left(base_ptr x) { return (link_type&)(x->left); }
		static link_type& right(base_ptr x) { return (link_type&)(x->right); }
		static reference value(base_ptr x) { return link_type(x)->value_field; }
		static const key_type& key(base_ptr x) { return KeyOfValue()(value(link_type(x))); }
		static colour_type& colour(base_ptr x) { return (colour_type&)(link_type(x)->colour); }

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
			_rb_tree_rebalance(newnode, root());
			++node_count;
			return iterator(newnode);
		}

		link_type _copy(link_type x, link_type p) {

		}

		void _erase(link_type x) {

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
				bad.what();
			}
		}
	public:
		/*
		*	构造与内存管理
		*/

		RB_tree(const Compare& comp = Compare()) :node_count(0), key_compare(comp) { init(); }

		~RB_tree() {
			auto clear = [](auto&& clear, link_type p) {
				if (p == nullptr) return;
				clear(clear, p->left);
				clear(clear, p->right);
				delete_node(p);
				};
			clear(clear, root());
			delete_node(header);
		}

		self& operator=(const self& x) {
			if (*this == x) return;

		}
	public:
		Compare key_comp() const { return key_compare; }
		iterator begin() { return leftmost(); }
		iterator end() { return header; }
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
