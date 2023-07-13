
"use strict";

let ObjectCount = require('./ObjectCount.js');
let BoundingBox = require('./BoundingBox.js');
let BoundingBoxes = require('./BoundingBoxes.js');
let CheckForObjectsGoal = require('./CheckForObjectsGoal.js');
let CheckForObjectsActionFeedback = require('./CheckForObjectsActionFeedback.js');
let CheckForObjectsAction = require('./CheckForObjectsAction.js');
let CheckForObjectsActionGoal = require('./CheckForObjectsActionGoal.js');
let CheckForObjectsResult = require('./CheckForObjectsResult.js');
let CheckForObjectsActionResult = require('./CheckForObjectsActionResult.js');
let CheckForObjectsFeedback = require('./CheckForObjectsFeedback.js');

module.exports = {
  ObjectCount: ObjectCount,
  BoundingBox: BoundingBox,
  BoundingBoxes: BoundingBoxes,
  CheckForObjectsGoal: CheckForObjectsGoal,
  CheckForObjectsActionFeedback: CheckForObjectsActionFeedback,
  CheckForObjectsAction: CheckForObjectsAction,
  CheckForObjectsActionGoal: CheckForObjectsActionGoal,
  CheckForObjectsResult: CheckForObjectsResult,
  CheckForObjectsActionResult: CheckForObjectsActionResult,
  CheckForObjectsFeedback: CheckForObjectsFeedback,
};
