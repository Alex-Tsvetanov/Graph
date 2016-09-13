#ifndef __lib_graph_unweight
#define __lib_graph_unweight
#include <abstract.hpp>
#include <vector>

namespace graph
{
	class unweight
	{
	private:
		class ln_edge 
		{
		public:
			std::size_t to;
			ln_edge (std::size_t _to = 0) : to (_to)
			{
			}
		};
		
		class le_edge
		{
		public:
			std::size_t from;
			std::size_t to;
			le_edge (std::size_t _from = 0, std::size_t _to = 0) : from (_from), to (_to)
			{
			}
		};
	public:
		class ln : public abstract1 <ln_edge, std::vector < std::vector < ln_edge > > >
		{
		public:
			void add (const std::size_t a, const std::size_t b)
			{
				std::size_t m = (a < b)?b:a;
				if (m >= l.size ())
					l.resize (m + 1);
				l [a].push_back (ln_edge (b));
			}
		};

		class le : public abstract1 <le_edge, std::vector < le_edge > >
		{
		public:
			void add (const std::size_t a, const std::size_t b)
			{
				l.push_back (le_edge (a, b));
			}
		};
	};
}

#endif
