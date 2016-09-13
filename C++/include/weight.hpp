#ifndef __lib_graph
#define __lib_graph
#include <abstract.hpp>
#include <vector>
#include <unweight.hpp>

namespace graph
{
	template <typename T>
	class weight
	{
	private:
		class ln_edge 
		{
		public:
			std::size_t to;
			T w;
			ln_edge (std::size_t _to = 0, T _w = T ()) : to (_to), w (_w)
			{
			}
		};
		
		class le_edge
		{
		public:
			std::size_t from;
			std::size_t to;
			T w;
			le_edge (std::size_t _from = 0, std::size_t _to = 0, T _w = T ()) : from (_from), to (_to), w (_w)
			{
			}
		};
	public:
		class ln : public abstract2 < ln_edge, std::vector < std::vector < ln_edge > >, T>
		{
		public:
			void add (const std::size_t a, const std::size_t b, const T c)
			{
				std::size_t m = (a < b)?b:a;
				if (m >= l.size ())
					l.resize (m + 1);
				l [a].push_back (ln_edge (b, c));
			}

			graph::unweight::ln to_unweight () const
			{
				auto a = graph::unweight::ln ();
				for (std::size_t i = 0 ; i < l.size () ; i ++)
					for (auto& y : l [i])
						a.add (i, y.to);
				return std::move (a);
			}
		};
		
		class le : public abstract2 < le_edge, std::vector < le_edge >, T>
		{
		public:
			void add (const std::size_t a, const std::size_t b, const T c)
			{
				l.push_back (le_edge (a, b, c));
			}			

			graph::unweight::le to_unweight () const
			{
				auto a = graph::unweight::le ();
				for (auto& x : l)
					a.add (x.from, x.to);
				return std::move (a);
			}
		};
	};
}

#endif
