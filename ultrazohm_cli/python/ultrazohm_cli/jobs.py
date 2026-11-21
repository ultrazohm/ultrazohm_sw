"""Firmware job monitoring without owning or cancelling the service job."""

from .configuration import _stored


class FirmwareJob:
    """Poll a submitted job, draining final logs before reporting completion.

    The caller schedules polls and may stop at any time. Resume with the same
    job ID and offset. Poll failures preserve the offset for explicit retry.
    """

    def __init__(self, client, job_id, offset=0):
        self.client = client
        self.id = job_id
        self.offset = offset
        self.complete = False
        self.error = None

    def poll(self):
        reply = self.client.job(self.id, self.offset)
        progress = _stored("job_progress", {"offset": self.offset, "reply": reply})
        self.offset = progress["next_offset"]
        self.complete = progress["complete"]
        self.error = progress["error"]
        return reply

    def raise_for_status(self):
        if self.complete and self.error is not None:
            raise RuntimeError(f"Firmware job failed: {self.error}")
