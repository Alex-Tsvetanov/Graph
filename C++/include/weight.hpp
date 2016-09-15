#pragma once

#include <abstract.hpp>
#include <vector>
#include <unweight.hpp>

namespace graph
{
	namespace weight
	{
	template <typename T>
		class ln_edge 
		{
		public:
			std::size_t to;
			T w;
			ln_edge (std::size_t _to = 0, T _w = T ()) : to (_to), w (_w)
			{
			}
		};
		
	template <typename T>
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
	template <typename T>
		class ln : public graph::abstract::graph_weight_abstract < ln_edge<T>, std::vector < std::vector < ln_edge<T> > >, T>
		{
		public:
			std::vector < std::vector < ln_edge > > l;

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
		
	template <typename T>
		class le : public graph::abstract::graph_weight_abstract < le_edge<T>, std::vector < le_edge<T> >, T>
		{
		public:
			std::vector < le_edge > l;
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
		
	template <typename T>
		class matrix
		{
		public:
			using value_type = T;
			size_t cols;
			size_t rows;
			
			value_type** data;
			matrix ()
			{
				cols = 0;
				rows = 0;
				data = nullptr;
			}
			matrix (const size_t n)
			{
				rows = cols = n;
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
		
			void add (const std::size_t a, const std::size_t b, const T c)
			{
				data [a][b] = c;
			}
			
			void add2 (const std::size_t a, const std::size_t b, const T c)
			{
				add (a, b, c);
				add (b, a, c);
			}	

			graph::unweight::matrix to_unweight () const
			{
				auto a = graph::unweight::matrix (cols);
				for (std::size_t i = 0 ; i < rows ; i ++)
					for (std::size_t j = 0 ; j < rows ; j ++)
						if (data [i][j] != T ())
							a.add (i, j);
				return std::move (a);
			}

			graph::weight<T>::matrix operator+ (const graph::weight::matrix<T> &b)
			{
				if (cols != b.cols or rows != b.rows)
					throw "weight::matrix::operator+ : Not compatible";
				graph::weight<T>::matrix res (cols, rows);
				for (size_t i = 0 ; i < cols ; i ++)
					for (size_t j = 0 ; j < rows ; j ++)
					{
						res [i][j] = this -> operator[] (i)[j] + b [i][j];
					}
				return std::move (res);
			}

			graph::weight::matrix<T> operator* (const graph::weight::matrix<T> &b)
			{
				if (cols != b.rows)
					throw "weight::matrix::operator* : Not compatible";
					
				graph::weight::matrix<T> res (b.cols, rows);
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
