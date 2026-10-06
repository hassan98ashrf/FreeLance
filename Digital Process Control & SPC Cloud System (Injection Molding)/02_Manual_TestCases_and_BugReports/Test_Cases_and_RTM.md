# Test Cases & Requirements Traceability Matrix (RTM)
**Project:** Digital Process Control & SPC Cloud System  
**Phase:** 02 - Test Design & Manual Execution  
**Standard:** ISTQB® Black-Box Test Design Techniques  
**Prepared By:** Hassan Ashraf (QA Engineer)

---

## 1. Requirements Traceability Matrix (RTM Summary)

| Requirement ID | Requirement Description | Design Technique | Mapped Test Case IDs | Coverage |
| :--- | :--- | :--- | :--- | :---: |
| **FR-01.1, FR-01.2** | Role-Based Authentication & Screen Routing | Decision Table | `TC-AUTH-01` to `TC-AUTH-05` | 100% |
| **FR-01.3** | Persistent Login Session & Explicit Logout | State Transition | `TC-AUTH-06`, `TC-AUTH-07` | 100% |
| **FR-02.1, FR-02.2** | Production Parameters Logging (`production_screen`) | EP & Error Guessing | `TC-PROD-01` to `TC-PROD-03` | 100% |
| **FR-03.1** | Quality Inspection & Attribute Tests (`quality_screen`) | Decision Table | `TC-QUAL-01` to `TC-QUAL-04` | 100% |
| **FR-04.1, FR-04.2** | Cross-Check Discrepancy & Manager Overview | Integration / UI | `TC-MNGR-01`, `TC-CRSS-01` | 100% |
| **FR-05.1, FR-05.2** | Real-Time SPC Charts & $C_p / C_{pk}$ Math Engine | Mathematical Verification | `TC-SPC-01`, `TC-SPC-02` | 100% |
| **FR-06.1, FR-06.2** | Dynamic Chart Rendering & Auto-Scaling Y-Axis | Condition Testing | `TC-UI-01` to `TC-UI-03` | 100% |
| **FR-06.3** | Data Point Color Alerts (UCL / LCL Limits) | BVA & EP | `TC-ALRT-01` to `TC-ALRT-05` | 100% |
| **FR-06.4** | $C_p / C_{pk}$ Capability Badge Color Thresholds | Boundary Value Analysis (BVA) | `TC-BVA-01` to `TC-BVA-04` | 100% |
| **FR-06.5** | OCAP Corrective Action Logging | Functional | `TC-OCAP-01` | 100% |

---

## 2. ISTQB Test Design Models

### 2.1 Boundary Value Analysis (BVA) Model for $C_p / C_{pk}$ Badges (`FR-06.4`)
* **Partition 1 (Incapable - Red Badge):** $< 1.00$
* **Partition 2 (Marginal/Warning - Orange Badge):** $1.00 \le \text{Value} < 1.33$
* **Partition 3 (Capable/Safe - Green Badge):** $\ge 1.33$
* **Selected Boundary Test Values:** `0.99` (Max Invalid Red), `1.00` (Min Orange), `1.32` (Max Orange), `1.33` (Min Safe Green).

### 2.2 Decision Table for Quality Attribute Tests (`FR-03.1`)

| Conditions / Actions | Rule 1 | Rule 2 | Rule 3 | Rule 4 |
| :--- | :---: | :---: | :---: | :---: |
| **Condition 1:** Alcohol Test (اختبار الكحول) | Pass | Pass | Fail | Fail |
| **Condition 2:** Cross-Cut Test (اختبار التقطيع) | Pass | Fail | Pass | Fail |
| **Condition 3:** Dimensional & Weight $(\bar{X}, R)$ within Spec | Yes | Yes | Yes | No |
| **Action:** Allowed Final Lot Decision | **Accepted** | **Rejected** | **Rejected** | **Rejected (Critical)** |

---

## 3. Master Test Cases Suite

### Module 1: Authentication, RBAC & Session Persistence (`login_screen`)

| TC ID | Requirement | Test Scenario | Preconditions & Test Data | Test Steps | Expected Result | Priority |
| :--- | :--- | :--- | :--- | :--- | :--- | :---: |
| **TC-AUTH-01** | `FR-01.2` | Verify login routing for **Production** role | Valid Employee in Firestore (`role: "production"`) | 1. Open App.<br>2. Enter Production ID & Password.<br>3. Tap Login. | User is authenticated and routed directly to `production_screen`. | High |
| **TC-AUTH-02** | `FR-01.2` | Verify login routing for **Quality** role | Valid Employee (`role: "quality"`) | 1. Enter Quality ID & Password.<br>2. Tap Login. | User is routed directly to `quality_screen`. | High |
| **TC-AUTH-03** | `FR-01.2` | Verify login routing for **Cross-Check** role | Valid Employee (`role: "crosscheck"`) | 1. Enter Cross-Check credentials.<br>2. Tap Login. | User is routed directly to `cross_check_screen`. | Medium |
| **TC-AUTH-04** | `FR-01.2` | Verify login routing for **Manager** role | Valid Employee (`role: "manager"`) | 1. Enter Manager credentials.<br>2. Tap Login. | User is routed directly to `manager_screen`. | High |
| **TC-AUTH-05** | `FR-01.1` | Verify login rejection with invalid credentials | Invalid Password | 1. Enter valid ID & wrong password.<br>2. Tap Login. | Login fails; clear error snackbar/message is displayed. | Medium |
| **TC-AUTH-06** | `FR-01.3` | **Verify Persistent Login** across app restarts | User is logged in on `production_screen` | 1. Force-close the app from Android recent apps.<br>2. Re-launch the app. | App bypasses `login_screen` and opens directly on `production_screen`. | High |
| **TC-AUTH-07** | `FR-01.3` | **Verify Logout Button** functionality & session clearance | User is logged in | 1. Tap the **Logout** button in the AppBar/Drawer.<br>2. Close and re-launch the app. | User is redirected to `login_screen` and remains logged out upon restart. | High |

---

### Module 2: $C_p / C_{pk}$ Badge Thresholds – Boundary Value Analysis (`chart_screen`)

| TC ID | Requirement | Test Scenario | Test Data (Calculated $C_{pk}$) | Test Steps | Expected Result | Priority |
| :--- | :--- | :--- | :--- | :--- | :--- | :---: |
| **TC-BVA-01** | `FR-06.4` | Verify $C_{pk}$ badge color at upper boundary of Red zone (`0.99`) | Subgroup readings yielding **$C_{pk} = 0.99$** | 1. Submit inspection readings resulting in $C_{pk} = 0.99$.<br>2. Navigate to `chart_screen`. | $C_{pk}$ value displays `0.99` inside a **Red Badge** (Incapable Process). | Critical |
| **TC-BVA-02** | `FR-06.4` | Verify $C_{pk}$ badge color at lower boundary of Orange zone (`1.00`) | Subgroup readings yielding **$C_{pk} = 1.00$** | 1. Submit readings resulting in $C_{pk} = 1.00$.<br>2. Open `chart_screen`. | $C_{pk}$ value displays `1.00` inside an **Orange Badge** (Marginal Process). | Critical |
| **TC-BVA-03** | `FR-06.4` | Verify $C_{pk}$ badge color at upper boundary of Orange zone (`1.32`) | Subgroup readings yielding **$C_{pk} = 1.32$** | 1. Submit readings resulting in $C_{pk} = 1.32$.<br>2. Open `chart_screen`. | $C_{pk}$ value displays `1.32` inside an **Orange Badge**. | High |
| **TC-BVA-04** | `FR-06.4` | Verify $C_{pk}$ badge color at lower boundary of Green zone (`1.33`) | Subgroup readings yielding **$C_{pk} = 1.33$** | 1. Submit readings resulting in $C_{pk} = 1.33$.<br>2. Open `chart_screen`. | $C_{pk}$ value displays `1.33` inside a **Green Badge** (Capable Process). | Critical |

---

### Module 3: Control Chart Point Alerts – EP & BVA (`production_screen` & `chart_screen`)
*Baseline Mold Control Plan for Oil Temperature: `LCL = 40.0°C`, `UCL = 60.0°C`*

| TC ID | Requirement | Test Scenario | Input Data (`Oil Temp`) | Test Steps | Expected Result | Priority |
| :--- | :--- | :--- | :--- | :--- | :--- | :---: |
| **TC-ALRT-01** | `FR-06.3` | Verify point color just below LCL (Invalid Partition - BVA) | **`39.9°C`** | 1. Select Mold #01.<br>2. Enter Oil Temp = `39.9`.<br>3. Submit & view $I$-Chart. | Data point is plotted in **Red**; Out-of-Control alert is triggered. | High |
| **TC-ALRT-02** | `FR-06.3` | Verify point color exactly at LCL boundary | **`40.0°C`** | 1. Enter Oil Temp = `40.0`.<br>2. Submit & view $I$-Chart. | Data point is plotted in **Blue/Green** (In-Spec). | High |
| **TC-ALRT-03** | `FR-06.3` | Verify point color at nominal center (Valid Partition - EP) | **`50.0°C`** | 1. Enter Oil Temp = `50.0`.<br>2. Submit & view $I$-Chart. | Data point is plotted in **Blue/Green** (In-Spec). | Medium |
| **TC-ALRT-04** | `FR-06.3` | Verify point color exactly at UCL boundary | **`60.0°C`** | 1. Enter Oil Temp = `60.0`.<br>2. Submit & view $I$-Chart. | Data point is plotted in **Blue/Green** (In-Spec). | High |
| **TC-ALRT-05** | `FR-06.3` | Verify point color just above UCL (Invalid Partition - BVA) | **`60.1°C`** | 1. Enter Oil Temp = `60.1`.<br>2. Submit & view $I$-Chart. | Data point is plotted in **Red**; Out-of-Control alert is triggered. | High |

---

### Module 4: Smart Dynamic UI, Math Engine & Quality Checks

| TC ID | Requirement | Test Scenario | Preconditions & Data | Test Steps | Expected Result | Priority |
| :--- | :--- | :--- | :--- | :--- | :--- | :---: |
| **TC-UI-01** | `FR-06.1` | Verify **Dynamic Rendering** hides disabled mold parameters | Mold #04 in Firestore has `hasDryingTemp: false` | 1. Select Mold #04 in `production_screen`.<br>2. Navigate to `chart_screen`. | Drying Temp input field and its $I$-Chart are completely hidden. | High |
| **TC-UI-02** | `FR-06.2` | Verify **Auto-Scaling Y-Axis** (`MinY`, `MaxY`) on extreme outlier | Mold `UCL = 60.0`; Actual reading = `75.0` | 1. Submit outlier reading `75.0`.<br>2. Open `chart_screen`. | Chart dynamically expands `MaxY > 75.0` so both the UCL line and the red outlier point remain visible on screen. | Medium |
| **TC-SPC-01** | `FR-05.2` | Verify accuracy of background $\mu$, $\sigma$, $C_p$, and $C_{pk}$ calculations | 5 known weight samples with pre-calculated Minitab values | 1. Submit 5 weight readings in `quality_screen`.<br>2. Compare app's printed $C_p/C_{pk}$ with Minitab benchmark. | Calculated values match standard statistical formulas up to 2 decimal places. | Critical |
| **TC-QUAL-01** | `FR-03.1` | Verify Lot Rejection enforcement when **Cross-Cut Test** fails | `Alcohol = Pass`, `Cross-Cut = Fail` | 1. Open `quality_screen`.<br>2. Select Pass for Alcohol, Fail for Cross-Cut.<br>3. Attempt to mark Lot as Accepted. | System enforces/recommends **Rejected** status due to failed attribute test. | High |
| **TC-OCAP-01** | `FR-06.5` | Verify OCAP corrective action note is saved with out-of-spec reading | Reading `65.0°C` (`> UCL`); OCAP: *"Adjusted oil cooler valve"* | 1. Enter out-of-spec reading.<br>2. Select/Type OCAP corrective action.<br>3. Submit and check Firestore `inspections`. | Document in Firestore contains the exact OCAP string linked to the reading's `timestamp`. | High |