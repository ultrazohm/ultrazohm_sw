"""Cache pressure reports actual capacity failures, including oversized entries."""
from uz_dataviewer.sources import ByteCache


def test_pressure_on_eviction_and_oversize(monkeypatch):
    clock = [10.0]
    monkeypatch.setattr('uz_dataviewer.sources.time.monotonic', lambda: clock[0])
    cache = ByteCache(10)
    cache.put('a', 'first', 6)
    cache.put('b', 'second', 4)
    assert not cache.status()['limit_hit']  # Exactly full, nothing lost.
    cache.get('a')  # Most recently used entry must survive.
    cache.put('c', 'third', 4)
    assert cache.get('b') is None
    assert cache.get('a') == 'first'
    assert cache.status()['evictions'] == 1
    assert cache.status()['limit_hit']
    clock[0] += 6
    assert not cache.status()['limit_hit']
    assert cache.put('big', 'oversized', 11) == 'oversized'
    assert cache.get('big') is None
    assert cache.status()['oversized'] == 1
    assert cache.status()['limit_hit']
    cache.clear()
    assert cache.status() == dict(bytes=0, limit=10, evictions=0, oversized=0, limit_hit=False)


def test_budget_reduction_reports_eviction():
    cache = ByteCache(10)
    cache.put('a', object(), 8)
    cache.limit = 4
    cache.trim()
    assert cache.status()['bytes'] == 0
    assert cache.status()['evictions'] == 1
    assert cache.status()['limit_hit']
