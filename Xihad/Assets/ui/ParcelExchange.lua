local Utils = require "ui.StaticUtils"
local ParcelView = require "ui.ParcelView"

local parcelWindow = Utils.findWindow("ParcelPanel/ParcelExchange")

local ParcelExchange = {
	completeListeners = {},
	cancelListeners = {},
	master = ParcelView.new(
		CEGUI.toItemListbox(Utils.findWindow("MasterSlots", parcelWindow)),
		Utils.findWindow("MasterName", parcelWindow),
		Utils.findWindow("L2RArrow", parcelWindow),
		0.22),
	guest = ParcelView.new(
		CEGUI.toItemListbox(Utils.findWindow("GuestSlots", parcelWindow)),
		Utils.findWindow("GuestName", parcelWindow),
		Utils.findWindow("R2LArrow", parcelWindow),
		0.78),
		
	FrameWindow = parcelWindow,
	_model = nil,
}

function ParcelExchange:show(model)
	self._model = model
	local master, guest = self.master, self.guest
	master:setModel(model.masterName, model.masterParcel)
	guest:setModel(model.guestName, model.guestParcel)
	
	local adjustedWidth = math.max(master.listbox:getPixelSize().width,
		guest.listbox:getPixelSize().width)
	master:relayout(adjustedWidth)
	guest:relayout(adjustedWidth)

	Utils.fireEvent("_Open", self.FrameWindow)
	return self.FrameWindow:getParent()
end

function ParcelExchange:close()
	Utils.fireEvent("_Close", self.FrameWindow)
	self.master:reset()
	self.guest:reset()
end

function ParcelExchange:_onItemClick(e)
	local itemEntry = CEGUI.toMenuItem(CEGUI.toWindowEventArgs(e).window)
	
	self.master:onItemClick(itemEntry, self.guest)
	self.guest:onItemClick(itemEntry, self.master)
end

function ParcelExchange:_onComplete(e)
	for callback,_ in pairs(self.completeListeners) do
		callback("Complete", self._model)
	end
end

function ParcelExchange:_onTidy(e)
	self.master:tidyParcel()
	self.guest:tidyParcel()
end

function ParcelExchange:_onCancel(e)
	for callback, _ in pairs(self.cancelListeners) do
		callback("Cancel")
	end
end

function ParcelExchange:_changeListeners(listener, eventType, setting)
	if eventType == "Complete" then
		self.completeListeners[listener] = setting
	elseif eventType == "Cancel" then
		self.cancelListeners[listener] = setting
	else
		return { "Complete", "Cancel" }
	end
end

function ParcelExchange:addListener(listener, eventType)
	return self:_changeListeners(listener, eventType, true)
end

function ParcelExchange:removeListener(listener, eventType)
	return self:_changeListeners(listener, eventType, nil)
end

function ParcelExchange:init()
	local window = self.FrameWindow
	local wndSz = window:getParentPixelSize()
	local tidyBtn = window:getChild("Tidy")
	local okBtn = window:getChild("Complete")
	local btSize = tidyBtn:getPixelSize()
	local btY = Utils.newUDim(0, 0.9*wndSz.height-1.5*btSize.height)
	tidyBtn:setYPosition(btY)
	okBtn:setYPosition(btY)
	tidyBtn:setXPosition(Utils.newUDim(0.3, -0.5*btSize.width))
	okBtn:setXPosition(Utils.newUDim(0.7, -0.5*btSize.width))
	
	local closeBtn = window:getChild("Close")
	closeBtn:setXPosition(Utils.newUDim(1,-8-closeBtn:getPixelSize().width))
	closeBtn:setYPosition(Utils.newUDim(0, 8))
	
	local subscribeEvent = Utils.subscribeEvent
	local functional = require 'std.functional'

	subscribeEvent(tidyBtn, "Clicked", functional.bindself(self, '_onTidy'))
	subscribeEvent(okBtn, "Clicked", functional.bindself(self, '_onComplete'))
	subscribeEvent(closeBtn, "Clicked", functional.bindself(self, '_onCancel'))
	
	local itemClickHandler = functional.bindself(self, '_onItemClick')
	ParcelExchange.master:init("green", -1, itemClickHandler)
	ParcelExchange.guest:init("red", 0, itemClickHandler)	
end

return ParcelExchange