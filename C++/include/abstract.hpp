#pragma once

namespace graph
{
	/*abstract*/ class Graph 
	{
	public:
		std::size_t n, m;
	};

	namespace abstract
	{
		template <typename Tedge, typename Tlist>
		/*abstract*/ class graph_unweight_abstract
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
		/*abstract*/ class graph_weight_abstract
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
	}
}
