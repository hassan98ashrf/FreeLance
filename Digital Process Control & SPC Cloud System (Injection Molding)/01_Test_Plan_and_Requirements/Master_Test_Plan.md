# Master Test Plan (ISTQB® Compliant)
**Project:** Digital Process Control & SPC Cloud System  
**Application Type:** Flutter Mobile App + Firestore Backend + Google Sheets Web Archive  
**Author:** Hassan Ashraf - ISTQB® Certified QA Engineer  

---

## 1. Test Objective
To validate the functional accuracy, mathematical precision ($C_p/C_{pk}$), dynamic UI rendering, Cloud Firestore real-time synchronization, and Google Sheets archiving of the Digital Process Control & SPC system across all four user roles.

---

## 2. Test Scope & ISTQB Design Techniques Applied

| Feature / Module | Target Screen / Layer | ISTQB Test Design Technique |
| :--- | :--- | :--- |
| **Role-Based Access & Persistent Login** | `login_screen` & `employees` DB | **Decision Table Testing** (Roles vs. Target Screens) |
| **$C_p / C_{pk}$ Badge Color Thresholds** | `chart_screen` | **Boundary Value Analysis (BVA)** at `0.99`, `1.00`, `1.32`, `1.33` |
| **UCL / LCL Point Alerting** | `production_screen` & `chart_screen` | **Equivalence Partitioning (EP)** (Below LCL, Normal, Above UCL) |
| **Dynamic Chart Hiding/Showing** | `chart_screen` & `molds` DB | **State Transition / Condition Testing** (Active vs. Inactive Mold Parameters) |
| **Alcohol & Cross-Cut Tests** | `quality_screen` | **Decision Table Testing** (Pass/Fail combinations vs. Lot Acceptance) |
| **Firestore & Google Sheets Sync** | Backend APIs & Web Sheet | **Integration & End-to-End (E2E) Testing** |

---

## 3. Automation & Testing Tool Stack

1. **Manual Testing:** Excel / Jira for Test Case execution, RTM, and Defect Reporting.
2. **API & Backend Testing (Postman):** 
   * Testing Firebase Firestore REST endpoints (`molds`, `inspections`, `employees`).
   * Validating Google Sheets Webhook / Apps Script payload delivery.
3. **Mobile UI Automation (Appium 2 + Java + Maven + TestNG):**
   * Automating E2E scenarios on Android Emulator (`production_screen` data entry $\rightarrow$ `chart_screen` badge verification).
   * Using `AppiumBy.accessibilityId` (via Flutter `Semantics`) and `UiAutomator2`.
4. **Web UI Automation (Selenium WebDriver + Java):**
   * Verifying that submitted inspection logs appear accurately in the archived **Google Sheets** web interface / Web Dashboard.

---

## 4. Test Environment
* **Mobile Client:** Flutter Debug APK (`app-debug.apk`) running on Android Studio Emulator (Android 11+) & Xiaomi Redmi Note 8 Pro.
* **Automation Server:** Appium Server v3.8.0 (`UiAutomator2` driver).
* **IDE & Build Tool:** IntelliJ IDEA, Java JDK, Maven, TestNG.

---

## 5. Entry & Exit Criteria
* **Entry Criteria:** Flutter APK compiled in debug mode; Firestore test collections (`molds`, `employees`) seeded with baseline control plans; Appium server connected via ADB.
* **Exit Criteria:** 100% execution of BVA cases on $C_p/C_{pk}$ calculations; 0 Critical bugs in mathematical engine ($\mu, \sigma$); successful execution of Appium + Selenium E2E regression suite.