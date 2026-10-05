# Software Requirements Specification (SRS)
**Project Name:** Digital Process Control & SPC Cloud System (Injection Molding)  
**Tech Stack:** Flutter & Dart (Android/Tablet), Firebase Cloud Firestore, fl_chart, Google Sheets API  
**Author:** Hassan Ashraf (Mechatronics & QA Engineer)

---

## 1. System Overview & Architecture
The Digital Process Control & SPC application is a real-time cloud system designed to replace manual paper logs and desktop statistical software (e.g., Minitab) on the injection molding shop floor. 

### 1.1 Backend Collections (Cloud Firestore)
* **`molds` Collection:** Stores the Control Plan and standard engineering tolerance limits (UCL/LCL) per mold.
* **`inspections` Collection:** Stores daily inspection records with exact `timestamp`, inspector name, shift, parameters, and OCAP notes.
* **`employees` Collection:** Manages user credentials and role-based permissions.
* **External Integration:** Real-time/Batch synchronization with **Google Sheets** for backup and audit archiving.

---

## 2. Functional Requirements (FR)

### FR-01: Authentication & Role-Based Routing (`login_screen`)
* **FR-01.1:** The system shall authenticate users against the `employees` Firestore collection.
* **FR-01.2 (Role Routing):** Upon login, the system shall route users directly to their authorized screen based on role:
  * *Production Role* $\rightarrow$ `production_screen`
  * *Quality Role* $\rightarrow$ `quality_screen`
  * *Cross-Check / Supervisor* $\rightarrow$ `cross_check_screen`
  * *Manager Role* $\rightarrow$ `manager_screen`
* **FR-01.3 (Session Persistence):** The device shall remain logged in across app restarts until the user explicitly clicks the **Logout** button.

### FR-02: Production Operations Logging (`production_screen`)
* **FR-02.1:** Production technicians/engineers shall select an active mold from the `molds` collection.
* **FR-02.2:** Users shall input periodic machine operating parameters:
  1. Oil Temperature (حرارة الزيت)
  2. Drying Temperature (حرارة التجفيف)
  3. Water Heater Temperature (سخان الماء)
  4. Dosing / Cushion (العيار)
  5. Production Quantity & Scrap/Reject Quantity (كميات الإنتاج والهالك).

### FR-03: Quality Assurance Inspection (`quality_screen`)
* **FR-03.1:** Quality inspectors shall input sample measurements:
  1. Sample Weights: Mean ($\bar{X}$) and Range ($R$).
  2. Critical Dimensions (الأبعاد).
  3. Visual/Chemical Attribute Tests: Alcohol Test (اختبار الكحول) & Cross-cut Test (Pass / Fail).
  4. Final Lot Decision: Accepted (قبول) or Rejected (رفض).

### FR-04: Cross-Check & Executive Monitoring (`cross_check_screen` & `manager_screen`)
* **FR-04.1:** `cross_check_screen` shall display side-by-side comparisons of Production readings vs. Quality readings to detect measurement discrepancies.
* **FR-04.2:** `manager_screen` shall provide a real-time overview of all active machines, current shift status, and active out-of-spec alarms across the shop floor.

### FR-05: Real-Time SPC Charts & Mathematical Engine (`chart_screen`)
* **FR-05.1 (Control Charts):** Using `fl_chart`, the system shall immediately plot:
  * **$\bar{X}$-Chart & $R$-Chart:** For sample weights and dimensions.
  * **$I$-Charts (Individual):** For Oil Temp, Drying Temp, Water Heater, and Cushion.
* **FR-05.2 ($C_p$ & $C_{pk}$ Engine):** The system shall automatically calculate Mean ($\mu$), Standard Deviation ($\sigma$), Potential Capability ($C_p$), and Actual Capability ($C_{pk}$) in the background and display them below each chart.

### FR-06: Smart UI/UX, Visual Alerts & OCAP
* **FR-06.1 (Dynamic Rendering):** If a selected mold's Control Plan in Firestore has disabled parameters (e.g., `hasDryingTemp == false` or `hasOilTemp == false`), the corresponding input fields and $I$-Charts shall be hidden automatically.
* **FR-06.2 (Auto-Scaling Axes):** Chart Y-axes (`MinY`, `MaxY`) shall dynamically scale based on actual min/max readings compared against `UCL` and `LCL` so data lines remain centered.
* **FR-06.3 (Data Point Color Rules):**
  * Reading within `[LCL, UCL]` $\rightarrow$ **Blue / Green Point**.
  * Reading `< LCL` or `> UCL` $\rightarrow$ **Red Point**.
* **FR-06.4 ($C_p$ & $C_{pk}$ Badge Color Boundaries - BVA Target):**
  * Value $\ge 1.33$ $\rightarrow$ **Green Badge** (Capable / Safe Process).
  * $1.00 \le \text{Value} < 1.33$ $\rightarrow$ **Orange Badge** (Warning / Marginal Process).
  * Value $< 1.00$ $\rightarrow$ **Red Badge** (Incapable Process - High Defect Risk).
* **FR-06.5 (OCAP - Out of Control Action Plan):** Users shall log delay reasons and corrective actions (e.g., *"Adjusted injection pressure and oil temp"* or *"Stable process - no action required"*) linked directly to the inspection timestamp.