#pragma once

#include <abstract.hpp>
#include <vector>

namespace graph
{
	namespace unweight
	{
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
		class ln : public graph::Graph, graph::abstract::graph_unweight_abstract <ln_edge, std::vector < std::vector < ln_edge > > >
		{
		public:
			void add (const std::size_t a, const std::size_t b)
			{
				std::size_t max = (a < b)?b:a;
				if (m >= l.size ())
					l.resize (max + 1);
				l [a].push_back (ln_edge (b));
				m ++;
			}
		};

		class le : public graph::Grpah, graph::abstract::graph_unweight_abstract <le_edge, std::vector < le_edge > >
		{
		public:
			void add (const std::size_t a, const std::size_t b)
			{
				l.push_back (le_edge (a, b));
				m ++;
			}
		};
		
		class matrix : public graph::Graph
		{
		public:
			using value_type = bool;
			size_t cols;
			size_t rows;
			
			value_type** data;
			matrix ()
			{
				cols = 0;
				rows = 0;
				data = nullptr;
			}
			matrix (const size_t _n)
			{
				rows = cols = n = _n;
				data = new value_type* [cols];
				for (size_t i = 0 ; i < cols ; i ++)
					data [i] = new value_type [rows];
			}

			value_type* operator[] (size_t i)
			{
				if (i >= cols)
					throw std::out_of_range ("matrix <T>::operator[]: Index out-of-range");
				return data [i];
			}
			const value_type* operator[] (size_t i) const
			{
				if (i >= cols)
					throw std::out_of_range ("matrix <T>::operator[]: Index out-of-range");
				return data [i];
			}
		
			void add (const std::size_t a, const std::size_t b)
			{
				m ++;
				data [a][b] = true;
			}
			
			void add2 (const std::size_t a, const std::size_t b)
			{
				add (a, b);
				add (b, a);
			}	

			graph::unweight::matrix operator+ (const graph::unweight::matrix &b)
			{
				if (cols != b.cols or rows != b.rows)
					throw "weight::matrix::operator+ : Not compatible";
				graph::unweight::matrix res (cols);
				for (size_t i = 0 ; i < cols ; i ++)
					for (size_t j = 0 ; j < rows ; j ++)
					{
						res [i][j] = this -> operator[] (i)[j] + b [i][j];
					}
				return std::move (res);
			}

			graph::unweight::matrix operator* (const graph::unweight::matrix &b)
			{
				if (cols != b.rows)
					throw "weight::matrix::operator* : Not compatible";
					
				graph::unweight::matrix res (b.cols);
				for (size_t j = 0 ; j < b.cols ; j ++)
				{
					for(size_t i = 0 ; i < cols ; i ++) 
					{
						res [j][i] = 0;
						for(size_t k = 1 ; k < rows ; k ++) 
							res [j][i] += this->operator[](j)[k] * b [k][i];
					}
				}
				return std::move (res);
			}
		};
	};
}
