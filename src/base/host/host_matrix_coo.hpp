/* ************************************************************************
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * ************************************************************************ */

#ifndef ROCALUTION_HOST_MATRIX_COO_HPP_
#define ROCALUTION_HOST_MATRIX_COO_HPP_

#include "../base_vector.hpp"
#include "../base_matrix.hpp"
#include "../matrix_formats.hpp"

namespace rocalution {

template <typename ValueType>
class HostMatrixCOO : public HostMatrix<ValueType>
{
    public:
    HostMatrixCOO();
    HostMatrixCOO(const Rocalution_Backend_Descriptor local_backend);
    virtual ~HostMatrixCOO();

    virtual void Info(void) const;
    virtual unsigned int GetMatFormat(void) const { return COO; }

    virtual void Clear(void);
    virtual void AllocateCOO(int nnz, int nrow, int ncol);

    virtual void SetDataPtrCOO(int** row, int** col, ValueType** val, int nnz, int nrow, int ncol);
    virtual void LeaveDataPtrCOO(int** row, int** col, ValueType** val);

    virtual bool Scale(ValueType alpha);
    virtual bool ScaleDiagonal(ValueType alpha);
    virtual bool ScaleOffDiagonal(ValueType alpha);
    virtual bool AddScalar(ValueType alpha);
    virtual bool AddScalarDiagonal(ValueType alpha);
    virtual bool AddScalarOffDiagonal(ValueType alpha);

    virtual bool ConvertFrom(const BaseMatrix<ValueType>& mat);

    virtual bool Sort(void);
    virtual bool Permute(const BaseVector<int>& permutation);
    virtual bool PermuteBackward(const BaseVector<int>& permutation);

    virtual void CopyFromCOO(const int* row, const int* col, const ValueType* val);
    virtual void CopyToCOO(int* row, int* col, ValueType* val) const;

    virtual void CopyFrom(const BaseMatrix<ValueType>& mat);
    virtual void CopyTo(BaseMatrix<ValueType>* mat) const;

    virtual bool ReadFileMTX(const std::string);
    virtual bool WriteFileMTX(const std::string) const;

    virtual void Apply(const BaseVector<ValueType>& in, BaseVector<ValueType>* out) const;
    virtual void
    ApplyAdd(const BaseVector<ValueType>& in, ValueType scalar, BaseVector<ValueType>* out) const;

    private:
    MatrixCOO<ValueType, int> mat_;

    friend class BaseVector<ValueType>;
    friend class HostVector<ValueType>;
    friend class HostMatrixCSR<ValueType>;
    friend class HostMatrixDIA<ValueType>;
    friend class HostMatrixELL<ValueType>;
    friend class HostMatrixHYB<ValueType>;
    friend class HostMatrixDENSE<ValueType>;

    friend class HIPAcceleratorMatrixCOO<ValueType>;
};

} // namespace rocalution

#endif // ROCALUTION_HOST_MATRIX_COO_HPP_
