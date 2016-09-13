#ifndef __lib_graph_abstract_list
#define __lib_graph_abstract_list

template <typename Tedge, typename Tlist>
/*abstract*/ class abstract1
{
public:
	class edge : public Tedge
	{

	};

	Tlist l;

	virtual void add (const std::size_t a, const std::size_t b) = 0;
	void add2 (const std::size_t a, const std::size_t b)
	{
		add (a, b);
		add (b, a);
	}

	typename Tlist::reference operator [] (std::size_t i) const
	{
		return (typename Tlist::reference)l.at (i);
	}
};

template <typename Tedge, typename Tlist, typename W>
/*abstract*/ class abstract2
{
public:
	class edge : public Tedge
	{

	};

	Tlist l;

	virtual void add (const std::size_t a, const std::size_t b, const W c) = 0;
	void add2 (const std::size_t a, const std::size_t b, const W c)
	{
		add (a, b, c);
		add (b, a, c);
	}

	typename Tlist::reference operator [] (std::size_t i) const
	{
		return (typename Tlist::reference)l.at (i);
	}
};

#endif
