/* ************************************************************************
 * Copyright (C) 2018-2024 Advanced Micro Devices, Inc. All rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ************************************************************************ */

#ifndef ROCALUTION_HOST_MATRIX_MCSR_HPP_
#define ROCALUTION_HOST_MATRIX_MCSR_HPP_

#include "../base_matrix.hpp"
#include "../base_vector.hpp"
#include "../matrix_formats.hpp"

namespace rocalution
{

    template <typename ValueType>
    class HostMatrixMCSR : public HostMatrix<ValueType>
    {
    public:
        HostMatrixMCSR();
        explicit HostMatrixMCSR(const Rocalution_Backend_Descriptor& local_backend);
        virtual ~HostMatrixMCSR();

        virtual void         Info(void) const;
        virtual unsigned int GetMatFormat(void) const
        {
            return MCSR;
        }

        virtual void Clear(void);
        virtual void AllocateMCSR(int64_t nnz, int nrow, int ncol);
        virtual void SetDataPtrMCSR(
            int** row_offset, int** col, ValueType** val, int64_t nnz, int nrow, int ncol);
        virtual void LeaveDataPtrMCSR(int** row_offset, int** col, ValueType** val);

        virtual bool ConvertFrom(const BaseMatrix<ValueType>& mat);

        virtual void CopyFrom(const BaseMatrix<ValueType>& mat);
        virtual void CopyTo(BaseMatrix<ValueType>* mat) const;

        virtual bool ILU0Factorize(void);

        virtual void LUAnalyse(void);
        virtual void LUAnalyseClear(void);
        virtual bool LUSolve(const BaseVector<ValueType>& in, BaseVector<ValueType>* out) const;

        virtual bool ReadFileRSIO(const std::string& filename);
        virtual bool WriteFileRSIO(const std::string& filename) const;

        virtual void Apply(const BaseVector<ValueType>& in, BaseVector<ValueType>* out) const;
        virtual void ApplyAdd(const BaseVector<ValueType>& in,
                              ValueType                    scalar,
                              BaseVector<ValueType>*       out) const;

    private:
        MatrixMCSR<ValueType, int> mat_;

        friend class BaseVector<ValueType>;
        friend class HostVector<ValueType>;
        friend class HostMatrixCSR<ValueType>;
        friend class HostMatrixCOO<ValueType>;
        friend class HostMatrixHYB<ValueType>;
        friend class HostMatrixDENSE<ValueType>;

        friend class HIPAcceleratorMatrixMCSR<ValueType>;
    };

} // namespace rocalution

#endif // ROCALUTION_HOST_MATRIX_MCSR_HPP_
