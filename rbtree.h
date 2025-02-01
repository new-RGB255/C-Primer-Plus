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
			*	������ָ��end()ʱ����RB_tree�е���Сֵ
			*/
			node = node->left;
		}
		else if (node->right) {
			/*
			*	�������ӽڵ�,��������С�Ľڵ�
			*/
			node = node->right;
			while (node->left) {
				node = node->left;
			}
		}
		else {
			/*
			*	û�����ӽڵ�,�ҳ��丸�ڵ�
			*	�����нڵ㱾���Ǹ����ӽڵ�,��һֱ����
			*	ֱ������Ϊ���ӽڵ�Ϊֹ��
			*/
			base_ptr ptr = node->parent;
			while (node == ptr->right) {
				node = ptr;
				ptr = ptr->parent;
			}
			/*
			*	����ʱ�����ӽڵ㲻Ϊ��ʱ�ĸ��ڵ�,���ʱ�ĸ��ڵ�Ϊ���
			*	����ԭ��node�ڵ�ָ��RB_tree�е����ڵ�,��ʱ������ָ��end()
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
			*	������ָ��end()ʱ����RB_tree�е����ֵ
			*/
			node = node->right;
		}
		else if (node->left) {
			/*
			*	�������ӽڵ�,�����������ҷ�֧�����Ľڵ�
			*/
			base_ptr ptr = node->left;
			while (ptr->right) {
				ptr = ptr->right;
				node = ptr;
			}
		}
		else {
			/*
			*	û�����ӽڵ�,�ҳ��丸�ڵ�
			*	�����нڵ㱾���Ǹ����ӽڵ�,��һֱ����
			*	ֱ������Ϊ���ӽڵ�Ϊֹ��
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
		*	����,������ɾ���ڵ�
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
		size_type node_count; // �ڵ����
		link_type header; // ������ʵ�ּ���,�ýڵ�ΪRB_tree��end(),����ڵ㻥Ϊ���ڵ�
		Compare key_compare; // ���Ĵ�С�Ƚ�׼��, function object

		// ��ȡheader�ĳ�Ա

		link_type& root(link_type x) const { return (link_type&)(header->parent); } // ��ȡ���ڵ�
		link_type& leftmost(link_type x) const { return (link_type&)(header->left); } // ��ȡ��Сֵ
		link_type& rightmost(link_type x) const { return (link_type&)(header->right); } // ��ȡ���ֵ

		// ��ȡ�ڵ�x�ĳ�Ա

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

		// ��ȡ����ֵ�ͼ�Сֵ

		static link_type maximum(link_type x) { return (link_type)_rb_tree_node_base::maximum(x); }
		static link_type minimum(link_type x) { return (link_type)_rb_tree_node_base::minimum(x); }
	public:
		//iterator
		using iterator = _rb_tree_iterator<value_type, reference, pointer>;
	private:
		iterator _insert(base_ptr _x, base_ptr _y, const value_type& v) {
			// ����_xΪ��ֵ�����,����_yΪ�����֮���ڵ�,����vΪ��ֵ

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
			// �½ڵ����ɫ����_rb_tree_rebalance()�е���
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
		*	�������ڴ����
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
			link_type x = root(); // �Ӹ��ڵ㿪ʼ
			while (x) { // �Ӹ��ڵ㿪ʼ,����Ѱ���ʵ��Ĳ����
				y = x;
				x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
			}
			return _insert(x, y, v);
		}

		std::pair<iterator, bool> insert_unique(const value_type& v) {
			/*
			*	������ֵ:�ڵ��ֵ�������ظ�,���ظ��������Ч
			*	ע��,����ֵ��һ��pair,����pair.first��һ��RB_tree�ĵ�����,ָ�������ڵ�
			*	pair.second��ʾ�����Ƿ�ɹ�
			*/

			link_type y = header;
			link_type x = root(); // �Ӹ��ڵ㿪ʼ
			bool compare = true;
			while (x) { // �Ӹ��ڵ㿪ʼ,����Ѱ���ʵ��Ĳ����
				y = x;
				compare = key_compare(KeyOfValue()(v), key(x));
				x = compare ? left(x) : right(x);
			}
			// �˳�whileѭ����y��ָ��Ϊ�����֮���ڵ�(��ʱ������ΪҶ�ڵ�)

			iterator j = iterator(y); // �������jָ������֮���ڵ�y
			if (compare) { // ���˳�whileѭ��ʱcompareΪtrue,��ʾ�¼�ֵ<�����֮���ڵ�ļ�ֵ,���������
				if (j == begin()) { // �������֮���ڵ�Ϊ����ڵ�
					return std::pair<iterator, bool>(_insert(x, y, v), true);
				}
				else { // ��������֮���ڵ㲻Ϊ����ڵ�,�¼�ֵ������ǰ��ļ�ֵ�ظ�
					--j; // ���ݵ�y�ĸ��ڵ�
				}
			}
			if (key_compare(key(j.node), KeyOfValue()(v))) { // y�ĸ��ڵ�֮��ֵ���¼�ֵ�Ĵ�С,СΪ��
				// �¼�ֵ������нڵ�֮��ֵ�ظ�,ִ�в������
				return std::pair<iterator, bool>(_insert(x, y, v), true);
			}
			// ��������,��ʾ�¼�ֵһ�������м��нڵ�֮��ֵ�ظ�,��ִ�в������
			return std::pair<iterator, bool>(j, false);
		}
	};
}

inline void _rb_tree_rebalance(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
	/*
	*	xΪ�����,rootΪ���ڵ�
	*	��ִ�в��������RB_tree���ʱ��ƻ�(ֻ����Υ����Ҷ�ںͲ����),�������ֵ������:
	*	1) �����Ϊ���ڵ�
	*   2) �����Ĳ����ڵ�Ϊ��ɫ
	*   3) �����Ĳ����ڵ�Ϊ��ɫ
	*/
	while (x != root && x->parent->colour == _rb_tree_red) { // ���ڵ�Ϊ��
		if (x->parent == x->parent->parent->left) { // ���ڵ�Ϊ�游�ڵ�֮��ڵ�
			_rb_tree_node_base* y = x->parent->parent->right; // ��yΪ�����ڵ�
			if (y && y->colour == _rb_tree_red) { // �����ڵ���Ϊ��
				x->parent->colour = _rb_tree_black; // ���ĸ��ڵ�Ϊ��
				y->colour = _rb_tree_black; // ���Ĳ����ڵ�Ϊ��
				x->parent->parent->colour = _rb_tree_red; // �����游�ڵ�Ϊ��
				x = x->parent->parent; // ʹ�游�ڵ��Ϊ�����ڵ����ϼ��,�ж�RB_tree�����Ƿ��ƻ�
			}
			else { // �޲����ڵ�򲮸��ڵ�Ϊ��
				if (x == x->parent->right) {
					x = x->parent;
					_rb_tree_rotate_left(x, root); // ��һ����Ϊ������
				}
				x->parent->colour = _rb_tree_black; // ������ɫ
				x->parent->parent->colour = _rb_tree_red;
				_rb_tree_rotate_right(x->parent->parent, root); // ��һ����Ϊ������
			}
		}
		else { // ���ڵ�Ϊ�游�ڵ�֮�ҽڵ�,������ж��߼��븸�ڵ�Ϊ��ڵ�����
			_rb_tree_node_base* y = x->parent->parent->left; 
			if (y && y->colour == _rb_tree_red) { // �����ڵ���Ϊ��
				x->parent->colour = _rb_tree_black; // ���ĸ��ڵ�Ϊ��
				y->colour = _rb_tree_black; // ���Ĳ����ڵ�Ϊ��
				x->parent->parent->colour = _rb_tree_red; // �����游�ڵ�Ϊ��
				x = x->parent->parent; // ʹ�游�ڵ��Ϊ�����ڵ����ϼ��,�ж�RB_tree�����Ƿ��ƻ�
			}
			else { // �޲����ڵ�򲮸��ڵ�Ϊ��
				if (x == x->parent->left) {
					x = x->parent;
					_rb_tree_rotate_right(x, root); // ��һ����Ϊ������
				}
				x->parent->colour = _rb_tree_black; // ������ɫ
				x->parent->parent->colour = _rb_tree_red;
				_rb_tree_rotate_left(x->parent->parent, root); // ��һ����Ϊ������
			}
		}
	} // while����
	root->colour = _rb_tree_black; // ���ڵ���ԶΪ��
}

inline void _rb_tree_rotate_left(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
	// xΪ��ת��

	_rb_tree_node_base* y = x->right; // yΪ��ת������ӽڵ�
	x->right = y->left;
	if (y->left) {
		y->left->parent = x;
	}
	// ��y��ȫ����x�ĵ�λ(y������ȫ����x�����й�ϵ)
	y->parent = x->parent;
	if (x == root) { // xΪ���ڵ�
		root = y;
	}
	else if (x == x->parent->left) { // xΪ�丸�ڵ�����ӽڵ�
		x->parent->left = y;
	}
	else { // xΪ�丸�ڵ�����ӽڵ�
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

inline void _rb_tree_rotate_right(_rb_tree_node_base* x, _rb_tree_node_base*& root) {
	// xΪ��ת��

	_rb_tree_node_base* y = x->left; // yΪ��ת������ӽڵ�
	x->left = y->right;
	if (y->right) {
		y->right->parent = x;
	}
	// ��y��ȫ����x�ĵ�λ(y������ȫ����x�����й�ϵ)
	y->parent = x->parent;
	if (x == root) { // xΪ���ڵ�
		root = y;
	}
	else if (x == x->parent->right) { // xΪ�丸�ڵ�����ӽڵ�
		x->parent->right = y;
	}
	else { // xΪ�丸�ڵ�����ӽڵ�
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}


#endif // !_RB_TREE_H_
