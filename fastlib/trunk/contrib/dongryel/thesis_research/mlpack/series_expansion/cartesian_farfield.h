/** @file cartesian_farfield.h
 *
 *  This file contains a templatized class implementing $O(D^p)$
 *  expansion for computing the coefficients for a far-field expansion
 *  for an arbitrary kernel function.
 *
 *  @author Dongryeol Lee (dongryel)
 *  @bug No known bugs.
 */

#ifndef MLPACK_SERIES_EXPANSION_CARTESIAN_FARFIELD_H
#define MLPACK_SERIES_EXPANSION_CARTESIAN_FARFIELD_H

#include "core/table/dense_matrix.h"
#include "core/table/dense_point.h"
#include "mlpack/series_expansion/series_expansion_aux.h"

namespace mlpack {
namespace series_expansion {

template<typename KernelAuxType>
class CartesianLocal;

/** @brief Far field expansion class in \f$O(D^p)\f$ expansion.
 *
 *  \f$O(D^p)\f$ expansion for a kernel is a traditional expansion
 *  generated by the multivariate Taylor expansion.
 */
template<typename KernelAuxType>
class CartesianFarField {

  private:

    ////////// Private Member Variables //////////

    /** @brief The center of the expansion. */
    core::table::DensePoint center_;

    /** @brief The coefficients. */
    core::table::DensePoint coeffs_;

    /** @brief The order of the expansion. */
    short int order_;

  public:

    ////////// Getters/Setters //////////

    /** @brief Gets the center of expansion.
     *
     *  @return The center of expansion for the current far-field expansion.
     */
    core::table::DensePoint* get_center() {
      return &center_;
    }

    const core::table::DensePoint* get_center() const {
      return &center_;
    }

    /** @brief Gets the set of far-field coefficients.
     *
     *  @return The const reference to the vector containing the
     *          far-field coefficients.
     */
    const core::table::DensePoint& get_coeffs() const {
      return coeffs_;
    }

    /** @brief Gets the approximation order.
     *
     *  @return The integer representing the current approximation order.
     */
    short int get_order() const {
      return order_;
    }

    /** @brief Gets the weight sum.
     */
    double get_weight_sum() const {
      return coeffs_[0];
    }

    /** @brief Sets the approximation order of the far-field expansion.
     *
     *  @param new_order The desired new order of the approximation.
     */
    void set_order(short int new_order) {
      order_ = new_order;
    }

    /** @brief Set the center of the expansion - assumes that the center
     *         has been initialized before...
     *
     *  @param center The center of expansion whose coordinate values
     *                will be copied to the center of the given far-field
     *                expansion object.
     */
    void set_center(const core::table::DensePoint &center) {
      for(index_t i = 0; i < center.length(); i++) {
        center_[i] = center[i];
      }
    }

    ////////// User-level Functions //////////

    /** @brief Accumulates the contribution of a single reference point as a
     *         far-field moment.
     *
     *  For the reference point $r$ and the current expansion centroid
     *  in the reference node \f$R\f$ as \f$R.c\f$, this function
     *  computes \f$\left( \frac{r - R.c}{kh} \right)^{\alpha}\f$ for
     *  \f$0 \leq \alpha \leq p\f$ where \f$\alpha\f$ is a
     *  \f$D\f$-dimensional multi-index and adds to the currently
     *  accumulated far-field moments: \f$ F(R) \leftarrow F(R) + w [
     *  \left( \frac{r - R.c}{kh} \right)^{\alpha}]_{0 \leq p \leq
     *  \alpha}\f$ where \f$F(R)\f$ is the current set of far-field
     *  moments for the reference node \f$R\f$. \f$k\f$ is an
     *  appropriate factor to multiply the bandwidth \f$h\f$ by; for the
     *  Gaussian kernel expansion, it is \f$\sqrt{2}\f$.
     *
     *  @param reference_point The coordinates of the reference point.
     *  @param weight The weight of the reference point v.
     *  @param order The order up to which the far-field moments should be
     *               accumulated up to.
     */
    void Accumulate(
      const core::table::DensePoint &reference_point, double weight, int order);

    /** @brief Accumulates the far field moment represented by the given
     *         reference data into the coefficients.
     *
     *  Given the set of reference points \f$r_{j_n} \in R\f$ in the
     *  reference node \f$R\f$, this function computes
     *  \f$\sum\limits_{r_{j_n} \in R} w_{j_n} \left( \frac{r_{j_n} -
     *  R.c}{kh} \right)^{\alpha}\f$ for \f$0 \leq \alpha \leq p\f$
     *  where \f$\alpha\f$ is a \f$D\f$-dimensional multi-index and adds
     *  to the currently accumulated far-field moments: \f$ F(R)
     *  \leftarrow F(R) + \left[ \sum\limits_{r_{j_n} \in R} w_{j_n}
     *  \left( \frac{r_{j_n} - R.c}{kh} \right)^{\alpha} \right]_{0 \leq
     *  p \leq \alpha}\f$ where \f$F(R)\f$ is the current set of
     *  far-field moments for the reference node \f$R\f$. \f$k\f$ is an
     *  appropriate factor to multiply the bandwidth \f$h\f$ by; for the
     *  Gaussian kernel expansion, it is \f$\sqrt{2}\f$.
     *
     *  @param data The entire reference dataset \f$\mathcal{R}\f$.
     *  @param weights The entire reference weights \f$\mathcal{W}\f$.
     *  @param begin The beginning index of the reference points for
     *               which we would like to accumulate the moments for.
     *  @param end The upper limit on the index of the reference points for
     *             which we would like to accumulate the moments for.
     *  @param order The order up to which the far-field moments should be
     *               accumulated up to.
     */
    void AccumulateCoeffs(
      const core::table::DenseMatrix& data,
      const core::table::DensePoint& weights,
      int begin, int end, int order);

    /** @brief Refine the far field moment that has been computed before
     *         up to a new order.
     */
    void RefineCoeffs(
      const core::table::DenseMatrix& data,
      const core::table::DensePoint& weights,
      int begin, int end, int order);

    /** @brief Evaluates the far-field coefficients at the given point.
     */
    double EvaluateField(
      const core::table::DenseMatrix& data, int row_num, int order) const;

    double EvaluateField(const double *x_q, int order) const;

    /** @brief Initializes the current far field expansion object with
     *         the given center.
     */
    void Init(const core::table::DensePoint& center, const TKernelAux &ka);
    void Init(const TKernelAux &ka);

    /** @brief Computes the required order for evaluating the far field
     *         expansion for any query point within the specified region
     *         for a given bound.
     */
    template<typename TBound>
    int OrderForEvaluating(
      const TBound &far_field_region,
      const TBound &local_field_region,
      double min_dist_sqd_regions,
      double max_dist_sqd_regions,
      double max_error, double *actual_error) const;

    /** @brief Computes the required order for converting to the local
     *         expansion inside another region, so that the total error
     *         (truncation error of the far field expansion plus the
     *         conversion error) is bounded above by the given user
     *         bound.
     *
     *  @return the minimum approximation order required for the error,
     *          -1 if approximation up to the maximum order is not possible.
     */
    template<typename TBound>
    int OrderForConvertingToLocal(
      const TBound &far_field_region,
      const TBound &local_field_region,
      double min_dist_sqd_regions,
      double max_dist_sqd_regions,
      double required_bound,
      double *actual_error) const;

    /** @brief Prints out the series expansion represented by this object.
     */
    void Print(const char *name = "", FILE *stream = stderr) const;

    /** @brief Translate from a far field expansion to the expansion
     *         here. The translated coefficients are added up to the
     *         ones here.
     */
    void TranslateFromFarField(const FarFieldExpansion &se);

    /** @brief Translate to the given local expansion. The translated
     *         coefficients are added up to the passed-in local
     *         expansion coefficients.
     */
    void TranslateToLocal(LocalExpansion<TKernelAux> &se, int truncation_order);
};
}
}

#endif
